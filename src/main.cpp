#include "Document.h"
#include "Indexer.h"
#include "Searcher.h"
#include "Tokenizer.h"
#include "WikiXmlParser.h"
#include <iostream>

class App {
  public:
    void save_index(std::string file_name) {
        WikiXmlParser wiki_xml_parser(file_name);
        wiki_xml_parser.parse();

        // Indexer indexer(documents);
        // indexer.output_storage();
    }

    void search() {
        std::string query;
        for (;;) {
            std::cout << "Query: ";
            std::cin >> query;
            if (query == "exit")
                break;

            std::vector<int> id_list = searcher_.search(query);
            if (id_list.empty()) {
                std::cout << "Zero match" << std::endl;
                continue;
            }

            for (int id : id_list) {
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
            app.save_index(argv[2]);
    } else {
        app.usage();
        exit(1);
    }
}
