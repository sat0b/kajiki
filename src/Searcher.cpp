#include "Searcher.h"
#include "Indexer.h"
#include "Tokenizer.h"
#include <algorithm>
#include <iostream>

Searcher::Searcher(std::map<std::string, std::vector<int>> postingList)
    : postingList_(std::move(postingList)) {}

void Searcher::loadIndex() {
  Indexer indexer;
  indexer.readStorage();
  postingList_ = indexer.getPostingList();
}

std::vector<int> Searcher::search(std::string query) {
  std::vector<int> idList;
  Tokenizer tokenizer(query);
  std::vector<std::string> bigrams = tokenizer.getBigram();
  for (std::string q : bigrams) {
    if (postingList_.count(q) > 0) {
      for (int documentId : postingList_[q]) {
        if (std::find(idList.begin(), idList.end(), documentId) == idList.end())
          idList.push_back(documentId);
      }
    }
  }
  return idList;
}
