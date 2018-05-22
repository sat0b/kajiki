#include "HTTPServer.h"
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>

HTTPServer::HTTPServer(std::string address, int port) :
        address_(address), port_(port ) {

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int errcode;
    if ((errcode = getaddrinfo(NULL)))
}