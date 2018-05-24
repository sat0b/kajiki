#ifndef KAJIKI_HTTPSERVER_H
#define KAJIKI_HTTPSERVER_H

#include <string>

class HTTPServer {
public:
    HTTPServer(char *service);
    void run();

private:
    int soc_;
    void send_recv(int acc);
};


#endif //KAJIKI_HTTPSERVER_H
