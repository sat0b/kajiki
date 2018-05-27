#include "Document.h"
#include "Indexer.h"
#include "Searcher.h"
#include "WikiXmlParser.h"
#include "Server.h"
#include <iostream>

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
      std::string body = "{\"Result\": {\"documentId\":[";
      for (int i = 0; i < idList.size(); i++) {
        int id = idList[i];
        body += std::to_string(id);
        if (i != idList.size() - 1)
          body += ",";
      }
      body += "]}}";
      Response response;
      response.setContentType("application/json");
      response.setBody(body);
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
