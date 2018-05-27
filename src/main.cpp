#include "Document.h"
#include "Indexer.h"
#include "Searcher.h"
#include "WikiXmlParser.h"
#include "Server.h"
#include <iostream>

class Json {
public:
  Json() = default;

  void addField(std::string key, std::string value) {
    json_ += quote(key) + ":" + quote(value) + ",";
  }

  void addField(std::string key, int value) {
    json_ += quote(key) + ":" + std::to_string(value) + ",";
  }

  void addField(std::string key, std::vector<int> values) {
    json_ += quote(key) + ":" + "[";
    for (int i = 0; i < values.size(); i++) {
      if (i != values.size() - 1)
        json_ += std::to_string(values[i]) + ",";
      else
        json_ += std::to_string(values[i]);
    }
    json_ += "],";
  }

  void addField(std::string key, Json json) {
    json_ += "\"" + key + "\":" + json.getString() + ",";
  }

  std::string getString() {
    return "{" + json_.substr(0, json_.length() - 1) + "}";
  }

private:
  std::string json_;

  std::string quote(std::string str) {
    return "\"" + str + "\"";
  }
};

class App {
public:
  App() : server_(8080) {}

  void saveIndex(std::string filename) {
    WikiXmlParser wikiXmlParser(filename, 10);
    std::vector<Document> documents;
    for (;;) {
      documents = wikiXmlParser.parseNext();
      if (documents.empty())
        break;
      Indexer indexer(documents);
      indexer.outputStorage();
    }
  }

  void search() {
    searcher_.loadIndex();
    server_.addHandler("/search", [=](Request request) {
      std::map<std::string, std::string> params = request.getParams();
      std::string query = params["query"];
      std::cout << "query: " << query << std::endl;
      std::vector<int> idList = searcher_.search(query);
      int nHit = static_cast<int>(idList.size());
      Json json, docJson;
      docJson.addField("documentId", idList);
      json.addField("Hit", nHit);
      json.addField("Query", query);
      json.addField("Result", docJson);
      Response response;
      response.setContentType("application/json");
      response.setBody(json.getString());
      return response;
    });
    server_.run();
  }

  void usage() {
    std::cout << "Usage: kajiki:\n";
    std::cout << "  -f string\n";
    std::cout << "      file_name (xml)\n";
    std::cout << "  -s\n";
    std::cout << "      server mode\n";
  }

private:
  Searcher searcher_;
  Server server_;
};

int main(int argc, char **argv) {
  App app;
  if (argc == 1) {
    app.search();
  } else if (argc > 1) {
    std::string option = argv[1];
    if (option == "-f")
      app.saveIndex(argv[2]);
    else if (option == "-s")
      app.search();
  } else {
    app.usage();
    exit(1);
  }
}
