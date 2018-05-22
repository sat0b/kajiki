#ifndef KAJIKI_HTTPSERVER_H
#define KAJIKI_HTTPSERVER_H

#include <string>

class HTTPServer {
public:
    HTTPServer(std::string address, int port);

private:
    std::string address_;
    int port_;

};


#endif //KAJIKI_HTTPSERVER_H
