#ifndef KAJIKI_SERVER_H
#define KAJIKI_SERVER_H

#include <functional>
#include <map>
#include <string>
#include <vector>

class Request {
public:
  explicit Request(std::string request);

  std::string getHeader(const std::string &header) {
    return headers_[header];
  }

  std::string getPattern() {
    return pattern_;
  }

  std::map<std::string, std::string> getParams();

private:
  std::string request_;
  std::string method_;
  std::string uri_;
  std::string version_;
  std::string pattern_;
  std::map<std::string, std::string> headers_;
  std::map<std::string, std::string> params_;
  void parseRequest();
  void parseURI();
};

class Response {
public:
  Response() = default;
  std::string getString();
  bool empty();
  void setContentType(std::string type);
  void setBody(std::string body);
  void setStatus(int statusCode);
  void setNotFound();

private:
  std::string body_;
  std::string type_;
  int statusCode_ = 200;
};

class Server {
public:
  explicit Server(int port);
  ~Server();
  void run();
  void addHandler(std::string pattern,
                  std::function<Response(Request)> handler);

private:
  int soc_;
  int port_;
  static bool killed;
  std::map<std::string, std::function<Response(Request)>> handlers_;
  void initSocket();
  void setSignal();
  Request recvRequest(int acc);
  void sendResponse(int acc, Request request);
  static void setKilled(int sig);
};

#endif // KAJIKI_SERVER_H
