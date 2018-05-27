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
        acc = accept(soc_, (struct sockaddr *)&from, &len);
        if (acc == -1) {
            if (errno != EINTR) {
                perror("accept");
            }
        } else {
            getnameinfo((struct sockaddr *)&from, len,
                        hbuf, sizeof(hbuf),
                        sbuf, sizeof(sbuf),
                        NI_NUMERICHOST|NI_NUMERICSERV);
            std::cerr << "Accept: " << hbuf << ":" << sbuf << "\n";
            Request request = recvRequest(acc);
            Response response = makeResponse(request);
            sendResponse(acc, response);
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
    char buf[512], *ptr;
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

Response Server::makeResponse(Request request) {
    std::string body = "<!DOCTYPE html><html><head><title>Test</title></head><body>Hello World</body></html>";
    return Response(body);
}

void Server::sendResponse(int acc, Response response) {
    std::string res = response.getString();
    ssize_t len = send(acc, res.c_str(), (size_t)res.length(), 0);
    std::cout << "response: " << response.getString();
    if (len == -1) {
        perror("send");
    }
}

Request::Request(std::string request) : request_(request) {
    parseRequest();
}

void Request::parseRequest() {
    std::istringstream iss(request_);
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
}

Response::Response(std::string body) {
    std::stringstream header;
    header << "HTTP/1.0 200 OK\r\n"
            << "Content-Length: " << body.length() << "\r\n"
            << "Content-type: text/html\r\n\r\n"
            << body;
    response_ = header.str();
}

std::string Response::getString() {
    return response_;
}

int main() {
    Server server("8080");
    server.run();
}
