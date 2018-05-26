#include "Document.h"
#include "Indexer.h"
#include "Searcher.h"
#include "Tokenizer.h"
#include "WikiXmlParser.h"
#include <iostream>

class App {
  public:
    void saveIndex(std::string file_name) {
        WikiXmlParser wikiXmlParser(file_name, 10);
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
        std::string query;
        for (;;) {
            std::cout << "Query: ";
            std::cin >> query;
            if (query == "exit")
                break;

            std::vector<int> idList = searcher_.search(query);
            if (idList.empty()) {
                std::cout << "Zero match" << std::endl;
                continue;
            }

            for (int id : idList) {
                std::cout << "document_id: " << id << "\n";
            }
        }
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
};

int main(int argc, char **argv) {
    App app;
    if (argc == 1) {
        app.search();
    } else if (argc == 3) {
        std::string option = argv[1];
        if (option == "-f")
            app.saveIndex(argv[2]);
    } else {
        app.usage();
        exit(1);
    }
}
