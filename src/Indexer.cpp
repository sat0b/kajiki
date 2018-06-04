#include "Indexer.h"
#include "Tokenizer.h"
#include <fstream>
#include <glog/logging.h>
#include <iostream>
#include <sstream>

const std::string Indexer::filename = "/tmp/kajiki.index";

Indexer::Indexer(std::vector<Document> documents) : documents(documents) {
  makePostingList();
}

void Indexer::makePostingList() {
  for (Document document : documents) {
    Tokenizer tokenizer(document.title);
    std::vector<std::string> bigrams = tokenizer.getBigram();
    for (std::string index : bigrams) {
      postingList_[index].push_back(document.id);
    }
  }
}

std::map<std::string, std::vector<int>> Indexer::getPostingList() {
  return postingList_;
}

void Indexer::outputStorage() {
  std::ofstream ofs(filename, std::ios::out);
  if (!ofs.is_open()) {
    LOG(ERROR) << "Cannot open " << filename << std::endl;
    exit(1);
  }
  for (auto posting : postingList_) {
    std::string index = posting.first;
    ofs << index << "\t";
    for (int documentID : posting.second)
      ofs << documentID << "\t";
    ofs << std::endl;
  }
}

void Indexer::readStorage() {
  char delimiter = '\t';
  std::ifstream ifs(filename, std::ios::in);
  if (!ifs.is_open()) {
    LOG(ERROR) << "Not found " << filename << std::endl;
    exit(1);
  }
  std::string line;
  while (getline(ifs, line)) {
    std::istringstream ss(line);
    std::string index;
    std::getline(ss, index, delimiter);
    std::string col;
    while (std::getline(ss, col, delimiter)) {
      int documentId = std::stoi(col);
      postingList_[index].push_back(documentId);
    }
  }
}
