#ifndef KAJIKI_SERVER_H
#define KAJIKI_SERVER_H

#include <string>
#include <map>
#include <vector>

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
    void addHandler(std::string pattern, std::function<Response(Request)> func);

private:
    int soc_;
    int port_;
    std::vector<std::function<Response(Request)>> handlers_;
    Request recvRequest(int acc);
    void sendResponse(int acc, Request request);
};

std::string makeHttpMessage(std::string body);

#endif //KAJIKI_SERVER_H
