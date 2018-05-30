#include "Document.h"
#include "Indexer.h"
#include "Searcher.h"
#include "WikiXmlParser.h"
#include "Server.h"
#include "Dictionary.h"
#include <iostream>
#include <glog/logging.h>

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
    json_ += quote(key) + ":" + json.getString() + ",";
  }

  void addField(std::string key, std::vector<Document> documents) {
    json_ += quote(key) + ":[";
    for (Document document : documents) {
      json_ += "{";
      json_ += quote("Title") + ": " + quote(document.title) + ",";
      json_ += quote("Text") + ": " + quote(document.text) + ",";
      json_ += quote("Id") + ": " + std::to_string(document.id);
      json_ += "},";
    }
    json_ = json_.substr(0, json_.length() - 1);
    json_ += "],";
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
  App() : server_(8080), dictionary_("/tmp/kajiki.dict") {}

  void saveIndex(std::string filename) {
    WikiXmlParser wikiXmlParser(filename, 10);
    std::vector<Document> documents;
    for (;;) {
      documents = wikiXmlParser.parseNext();
      if (documents.empty())
        break;
      Indexer indexer(documents);
      indexer.outputStorage();
      dictionary_.putAll(documents);
    }
  }

  void search() {
    searcher_.loadIndex();
    server_.addHandler("/search", [=](Request request) {
      std::map<std::string, std::string> params = request.getParams();
      std::string query = params["query"];
      LOG(INFO) << "query: " << query << std::endl;
      std::vector<int> idList = searcher_.search(query);
      std::vector<Document> documents = dictionary_.readAll(idList);
      int nHit = static_cast<int>(idList.size());
      Json json;
      json.addField("Hit", nHit);
      json.addField("Query", query);
      json.addField("Result", documents);
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
  Dictionary dictionary_;
};

// command line argument
DEFINE_bool(server, false, "server mode");
DEFINE_string(feedfile, "", "feed file");

int main(int argc, char **argv) {
  // Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  gflags::SetUsageMessage("A toy search-engine for wikidata");
  google::ParseCommandLineFlags(&argc, &argv, true);

  App app;
  if (FLAGS_server || FLAGS_feedfile.length() == 0) {
    app.search();
  } else {
    app.saveIndex(FLAGS_feedfile);
  }
}
