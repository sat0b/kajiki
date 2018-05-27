#include <iostream>
#include <fstream>
#include <sstream>
#include "Indexer.h"
#include "Tokenizer.h"

const std::string Indexer::fileName = "/tmp/kajiki.index";

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
  std::ofstream ofs(fileName, std::ios::out);
  if (!ofs.is_open()) {
    std::cerr << "Cannot open " << fileName << std::endl;
    exit(1);
  }
  for (auto posting : postingList_) {
    std::string index = posting.first;
    ofs << index << "\t";
    for (int document_id : posting.second)
      ofs << document_id << "\t";
    ofs << std::endl;
  }
  ofs.close();
}

void Indexer::readStorage() {
  char delimiter = '\t';
  std::ifstream ifs(fileName, std::ios::in);
  if (!ifs.is_open()) {
    std::cerr << "Not found " << fileName << std::endl;
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
  ifs.close();
}
