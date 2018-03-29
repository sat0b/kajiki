#include <iostream>
#include "XmlParser.h"
#include "XmlTree.h"
#include "Tokenizer.h"
#include "WikiLoader.h"
#include "Document.h"
#include "Indexer.h"

int main(int argc, char **argv) {
//    Tokenizer tokenizer("こんにちは世界");
//    auto bigrams = tokenizer.get_bigram();
//    std::cout << bigrams[0] << std::endl;
//    std::cout << bigrams[1] << std::endl;
//    std::cout << bigrams[2] << std::endl;

    XmlParser xml_parser;
    if (argc == 2) {
        std::string file_name = argv[1];
        xml_parser.open(file_name);
        XmlTree *root = xml_parser.parse();
        WikiLoader wiki_loader(root);
        std::vector<Document> documents = wiki_loader.load();
        Indexer indexer(documents);
        indexer.output();
    }
}
