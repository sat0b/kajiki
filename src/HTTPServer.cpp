#include "HTTPServer.h"
#include <sys/socket.h>

#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <string.h>


HTTPServer::HTTPServer(std::string address, int port) {
    char service = static_cast<char>(port);
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int errcode;
    if ((errcode = getaddrinfo(NULL, &service, &hints, &res)) != 0) {
        std::cerr << "getaddrinfo(): " << gai_strerror(errcode) << std::endl;
        exit(1);
    }
    char nbuf[NI_MAXHOST];
    char sbuf[NI_MAXSERV];
    if ((errcode = getnameinfo(
            res->ai_addr, res->ai_addrlen,
            nbuf, sizeof(nbuf),
            sbuf, sizeof(sbuf),
            NI_NUMERICHOST | NI_NUMERICSERV)) != 0) {
        std::cerr << "getnameinfo(): " << gai_strerror(errcode) << std::endl;
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
    if (setsockopt(soc_, SOL_SOCKET, SO_REUSEADDR, &opt, opt_len) != -1) {
        perror("setsockopt");
        close(soc_);
        freeaddrinfo(res);
        exit(1);
    }

    // bind address
    if (bind(soc_, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        close(soc_);
        freeaddrinfo(res);
        exit(1);
    }

    // access back log
    if (listen(soc_, SOMAXCONN) == -1) {
        perror("listen");
        close(soc_);
        exit(1);
    }
    freeaddrinfo(res);
}