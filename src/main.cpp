#include <iostream>
#include "XmlParser.h"
#include "XmlTree.h"
#include "Tokenizer.h"
#include "WikiLoader.h"
#include "Document.h"
#include "Indexer.h"
#include "Searcher.h"

void run_command_line(std::string file_name) {
    XmlParser xml_parser;
    xml_parser.open(file_name);
    WikiLoader wiki_loader(xml_parser.parse());
    std::vector<Document> documents = wiki_loader.load();
    Indexer indexer(documents);
    indexer.output_storage();
    Searcher searcher;

    std::string query;
    for (;;) {
        std::cout << "Query: ";
        std::cin >> query;
        if (query == "exit")
            break;

        std::vector<int> id_list = searcher.search(query);
        if (id_list.size() == 0) {
            std::cout << "Zero match" << std::endl;
            continue;
        }

        for (int id : id_list) {
            std::cout << "document_id: " << id << "\n";
        }
    }
}

int main(int argc, char **argv) {
    if (argc == 2) {
        run_command_line(argv[1]);
    }
}
