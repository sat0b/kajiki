#include <iostream>
#include "Indexer.h"
#include "Tokenizer.h"


Indexer::Indexer(std::vector<Document> documents) : documents(documents) {}

std::map<std::string, std::vector<int>> Indexer::output() {
    for (Document document : documents) {
        std::string title = document.get_title();
        int document_id = document.get_id();
        Tokenizer tokenizer(title);
        std::vector<std::string> bigrams = tokenizer.get_bigram();
        for (std::string index : bigrams) {
            posting_list[index].push_back(document_id);
        }
    }
    return posting_list;
}
