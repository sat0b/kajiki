#include <iostream>
#include "Indexer.h"
#include "Tokenizer.h"


Indexer::Indexer(std::vector<Document> documents) : documents(documents) {}

void Indexer::output() {
    for (Document document : documents) {
        std::string title = document.get_title();
        int document_id = document.get_id();
        Tokenizer tokenizer(title);
        std::vector<std::string> bigrams = tokenizer.get_bigram();
        for (std::string index : bigrams) {
            posting_list[index].push_back(document_id);
        }
    }
    for (auto index :  posting_list) {
        std::cout << index.first << ": ";
        for (auto id : index.second)
            std::cout << id << ",";
        std::cout << std::endl;
    }
}

