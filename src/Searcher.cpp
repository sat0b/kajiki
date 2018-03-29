#include "Searcher.h"
#include "Tokenizer.h"

Searcher::Searcher(std::map<std::string, std::vector<int>> posting_list) :
    posting_list(std::move(posting_list)) {}

std::vector<int> Searcher::search(std::string query) {
    std::vector<int> id_list;
    Tokenizer tokenizer(query);
    std::vector<std::string> bigrams = tokenizer.get_bigram();
    for (std::string q : bigrams) {
        if (posting_list.count(q) > 0) {
            id_list.insert(id_list.end(), posting_list[q].begin(), posting_list[q].end());
        }
    }
    return id_list;
}

