#include "HTTPServer.h"
#include <sys/socket.h>

#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <string.h>


HTTPServer::HTTPServer(char *service) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int errcode = getaddrinfo("localhost", service, &hints, &res);
    if (errcode != 0) {
        std::cerr << "getaddrinfo(): " << gai_strerror(errcode) << std::endl;
        exit(1);
    }

    char nbuf[NI_MAXHOST];
    char sbuf[NI_MAXSERV];
    errcode = getnameinfo(
        res->ai_addr, res->ai_addrlen,
        nbuf, sizeof(nbuf),
        sbuf, sizeof(sbuf),
        NI_NUMERICHOST | NI_NUMERICSERV);
    if (errcode != 0) {
        std::cerr << "getnameinfo(): " << gai_strerror(errcode) << std::endl;
        freeaddrinfo(res);
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

void HTTPServer::run() {
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
            fprintf(stderr, "accept:%s:%s\n", hbuf, sbuf);
            send_recv(acc);
            close(acc);
            acc = 0;
        }
    }
}

void HTTPServer::send_recv(int acc) {
    char buf[512], *ptr;
    ssize_t len;
    for (;;) {
        len = recv(acc, buf, sizeof(buf), 0);
        if (len == -1) {
            perror("recv");
            break;
        }
        if (len == 0) {
            std::cerr << "recv:EOF\n";
            break;
        }
        buf[len] = '\0';
        ptr = strpbrk(buf, "\r\n");
        if (ptr != NULL)
            *ptr = '\0';
        std::cerr << "[client] " << buf << std::endl;
        len = (ssize_t) strlen(buf);
        len = send(acc, buf, (size_t)len, 0);
        if (len == -1) {
            perror("send");
            break;
        }
    }
}
