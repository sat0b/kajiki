#ifndef KAJIKI_HTTPSERVER_H
#define KAJIKI_HTTPSERVER_H

#include <string>

class HTTPServer {
public:
    HTTPServer(std::string address, int port);

private:
    int soc_;
};


#endif //KAJIKI_HTTPSERVER_H
