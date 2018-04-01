#include <iostream>
#include "Searcher.h"
#include "Tokenizer.h"
#include "Indexer.h"

Searcher::Searcher(std::map<std::string, std::vector<int>> posting_list) :
    posting_list(std::move(posting_list)) {}

Searcher::Searcher() {
    Indexer indexer;
    indexer.read_storage();
    posting_list = indexer.get_posting_list();
}

std::vector<int> Searcher::search(std::string query) {
    std::vector<int> id_list;
    Tokenizer tokenizer(query);
    std::vector<std::string> bigrams = tokenizer.get_bigram();
    for (std::string q : bigrams) {
        if (posting_list.count(q) > 0) {
            for (int document_id : posting_list[q]) {
                if (std::find(id_list.begin(), id_list.end(), document_id) == id_list.end())
                    id_list.push_back(document_id);
            }
        }
    }
    return id_list;
}
