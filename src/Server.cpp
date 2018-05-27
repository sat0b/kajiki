#include "Server.h"
#include <sys/socket.h>

#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sstream>


Server::Server(std::string service) {
  // TODO: Error handling
  port_ = stoi(service);

  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int errcode = getaddrinfo("localhost", service.c_str(), &hints, &res);
  if (errcode != 0) {
    std::cerr << "getaddrinfo(): " << gai_strerror(errcode) << std::endl;
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

void Server::run() {
  std::cout << "Server is running on " << port_ << "...\n";
  char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
  struct sockaddr_storage from;
  socklen_t len;
  int acc;
  for (;;) {
    len = (socklen_t) sizeof(from);
    acc = accept(soc_, (struct sockaddr *) &from, &len);
    if (acc == -1) {
      if (errno != EINTR) {
        perror("accept");
      }
    } else {
      getnameinfo((struct sockaddr *) &from, len,
                  hbuf, sizeof(hbuf),
                  sbuf, sizeof(sbuf),
                  NI_NUMERICHOST | NI_NUMERICSERV);
      std::cerr << "Accept: " << hbuf << ":" << sbuf << "\n";
      Request request = recvRequest(acc);
      sendResponse(acc, request);
      close(acc);
      acc = 0;
    }
  }
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
  for (auto handler : handlers_) {
    std::string pattern = handler.first;
    std::function<Response(Request)> func = handler.second;
    Response response;
    if (request.getPattern() == pattern)
      response = func(request);
    else
      response.setNotFound();
    std::string res = response.getString();
    ssize_t len = send(acc, res.c_str(), (size_t) res.length(), 0);
    if (len == -1) {
      perror("send");
    }
  }
}

void Server::addHandler(std::string pattern, std::function<Response(Request)> func) {
  handlers_[pattern] = func;
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
