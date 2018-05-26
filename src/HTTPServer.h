#ifndef KAJIKI_HTTPSERVER_H
#define KAJIKI_HTTPSERVER_H

#include <string>

class HTTPServer {
public:
    HTTPServer(std::string service);
    ~HTTPServer();
    void run();

private:
    int soc_;
    int port_;
    std::string recv_request(int acc);
    void send_response(int acc, std::string response);
};

std::string make_http_message(std::string body);

#endif //KAJIKI_HTTPSERVER_H
