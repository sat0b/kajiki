#include "Server.h"
#include <cstring>
#include <glog/logging.h>
#include <iostream>
#include <netdb.h>
#include <signal.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(int port) : port_(port) {}

void Server::initSocket() {
  std::string service = std::to_string(port_);

  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int errcode = getaddrinfo("localhost", service.c_str(), &hints, &res);
  if (errcode != 0) {
    LOG(ERROR) << "getaddrinfo(): " << gai_strerror(errcode) << std::endl;
    exit(1);
  }

  // generate socket
  soc_ = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (soc_ == -1) {
    perror("socket");
    freeaddrinfo(res);
    exit(1);
  }

  // configure socket option
  int opt = 1;
  socklen_t opt_len = sizeof(opt);
  errcode = setsockopt(soc_, SOL_SOCKET, SO_REUSEADDR, &opt, opt_len);
  if (errcode == -1) {
    perror("setsockopt");
    close(soc_);
    freeaddrinfo(res);
    exit(1);
  }

  // bind address
  errcode = bind(soc_, res->ai_addr, res->ai_addrlen);
  if (errcode == -1) {
    perror("bind");
    close(soc_);
    freeaddrinfo(res);
    exit(1);
  }

  // access back log
  errcode = listen(soc_, SOMAXCONN);
  if (errcode == -1) {
    perror("listen");
    close(soc_);
    exit(1);
  }
  freeaddrinfo(res);
}

bool Server::killed = false;

void Server::setKilled(int sig) {
  killed = true;
}

void Server::setSignal() {
  struct sigaction act;
  act.sa_handler = setKilled;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  if (sigaction(SIGUSR1, &act, NULL) < 0) {
    perror("sigaction");
    std::exit(1);
  }
}

void Server::run() {
  initSocket();
  setSignal();

  LOG(INFO) << "Server is running on " << port_ << "...\n";
  char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
  struct sockaddr_storage from;
  socklen_t len;
  int acc;
  while (!killed) {
    len = (socklen_t)sizeof(from);
    acc = accept(soc_, (struct sockaddr *)&from, &len);
    if (acc == -1) {
      if (errno != EINTR) {
        perror("accept");
      }
    } else {
      getnameinfo((struct sockaddr *)&from, len, hbuf, sizeof(hbuf), sbuf,
                  sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
      LOG(INFO) << "Accept: " << hbuf << ":" << sbuf << "\n";
      Request request = recvRequest(acc);
      sendResponse(acc, request);
      close(acc);
    }
  }
  LOG(INFO) << "Server is terminated ..." << std::endl;
}

Server::~Server() {
  close(soc_);
}

Request Server::recvRequest(int acc) {
  std::string req;
  char buf[512];
  ssize_t len;
  for (;;) {
    len = recv(acc, buf, sizeof(buf), 0);
    if (len == -1) {
      perror("recv");
      break;
    }
    buf[len] = '\0';
    req += buf;
    if (len < sizeof(buf))
      break;
  }
  return Request(req);
}

void Server::sendResponse(int acc, Request request) {
  Response response;
  for (auto handler : handlers_) {
    std::string pattern = handler.first;
    std::function<Response(Request)> func = handler.second;
    if (request.getPattern() == pattern)
      response = func(request);
  }
  if (response.empty())
    response.setNotFound();
  std::string res = response.getString();
  ssize_t len = send(acc, res.c_str(), (size_t)res.length(), 0);
  if (len == -1) {
    perror("send");
  }
}

void Server::addHandler(std::string pattern,
                        std::function<Response(Request)> handler) {
  handlers_[pattern] = handler;
}

Request::Request(std::string request) : request_(request) {
  parseRequest();
}

void Request::parseRequest() {
  std::istringstream iss(request_);
  iss >> method_;
  iss >> uri_;
  iss >> version_;
  std::string line;
  while (getline(iss, line)) {
    std::istringstream isline(line);
    std::string key;
    std::string value;
    if (getline(isline, key, ':')) {
      getline(isline, value, ':');
      if (value[0] == ' ') {
        value = value.substr(1);
      }
    }
    headers_[key] = value;
  }
  parseURI();
}

std::map<std::string, std::string> Request::getParams() {
  return params_;
}

void Request::parseURI() {
  std::stringstream ss(uri_);
  getline(ss, pattern_, '?');
  std::string param;
  while (getline(ss, param, '&')) {
    std::stringstream paramss(param);
    std::string key, value;
    getline(paramss, key, '=');
    getline(paramss, value, '=');
    params_[key] = value;
  }
}

void Response::setContentType(std::string type) {
  type_ = type;
}

void Response::setBody(std::string body) {
  body_ = body;
}

void Response::setStatus(int statusCode) {
  statusCode_ = statusCode;
}

void Response::setNotFound() {
  setContentType("text/plain");
  setStatus(404);
  setBody("404 page not found");
}

std::string Response::getString() {
  std::stringstream res;
  res << "HTTP/1.1 ";
  if (statusCode_ == 200)
    res << "200 OK\r\n";
  else
    res << "404 Not Found\r\n";
  res << "Content-type: " << type_ << "\r\n";
  res << "X-Content-Type-Options: nosniff\r\n";
  res << "Content-Length: " << body_.length() << "\r\n";
  res << "\r\n";
  res << body_ << "\n";
  return res.str();
}

bool Response::empty() {
  return body_.length() == 0;
}
