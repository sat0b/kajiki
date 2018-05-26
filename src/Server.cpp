#include "Server.h"
#include <sys/socket.h>

#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sstream>


HTTPServer::HTTPServer(std::string service) {
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

void HTTPServer::run() {
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
            std::string request = recv_request(acc);
            HTTPRequest http_request(request);
            std::cout << request << std::endl;
            send_response(acc, request);
            close(acc);
            acc = 0;
        }
    }
}

HTTPServer::~HTTPServer() {
    close(soc_);
}

std::string HTTPServer::recv_request(int acc) {
    std::string request;
    char buf[512], *ptr;
    ssize_t len;
    for (;;) {
        len = recv(acc, buf, sizeof(buf), 0);
        if (len == -1) {
            perror("recv");
            break;
        }
        buf[len] = '\0';
        request += buf;
        if (len < sizeof(buf))
            break;
    }
    return request;
}

void HTTPServer::send_response(int acc, std::string request) {
    std::string body = "<!DOCTYPE html><html><head><title>Test</title></head><body>Hello World</body></html>";
    std::string response = make_http_message(body);
    std::cout << "response: " << response;
    ssize_t len = send(acc, response.c_str(), (size_t)response.length(), 0);
    if (len == -1) {
        perror("send");
    }
}

std::string make_http_message(std::string body) {
    std::stringstream message;
    message << "HTTP/1.0 200 OK\r\n"
            << "Content-Length: " << body.length() << "\r\n"
            << "Content-type: text/html\r\n\r\n"
            << body;
    return message.str();
}

HTTPRequest::HTTPRequest(std::string request) : request_(request) {
    parse_request();
}

void HTTPRequest::parse_request() {
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

int main() {
    HTTPServer server("8080");
    server.run();
}
