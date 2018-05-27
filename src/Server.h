#ifndef KAJIKI_SERVER_H
#define KAJIKI_SERVER_H

#include <string>
#include <map>

class Request {
public:
    explicit Request(std::string request);
    std::string getHeader(const std::string &header) {
        return headers_[header];
    }
private:
    std::string request_;
    void parseRequest();
    std::map<std::string, std::string> headers_;
};

class Response {
public:
    explicit Response(std::string body);
    std::string getString();
private:
    std::string response_;
};

class Server {
public:
    explicit Server(std::string service);
    ~Server();
    void run();

private:
    int soc_;
    int port_;
    std::string recvRequest(int acc);
    void sendResponse(int acc, std::string response);
};

std::string makeHttpMessage(std::string body);

#endif //KAJIKI_SERVER_H
