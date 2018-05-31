#include "Dictionary.h"
#include "Document.h"
#include <algorithm>
#include <fstream>
#include <glog/logging.h>
#include <iostream>

Dictionary::Dictionary(std::string path) : path_(path) {}

Dictionary::~Dictionary() {}

std::vector<Document> Dictionary::readAll(std::vector<int> documentIds) {
  std::vector<Document> documents;
  std::ifstream ifs(path_);
  if (!ifs.is_open()) {
    LOG(ERROR) << "Cannot open " << path_ << std::endl;
    exit(1);
  }
  std::string line;
  while (getline(ifs, line)) {
    std::stringstream ssline(line);
    int id;
    ssline >> id;
    if (std::count(documentIds.begin(), documentIds.end(), id) > 0) {
      std::string title;
      std::string text;
      ssline >> title >> text;
      documents.emplace_back(id, title, text);
    }
  }
  ifs.close();
  return documents;
}

void Dictionary::putAll(std::vector<Document> documents) {
  std::ofstream ofs(path_);
  if (!ofs.is_open()) {
    LOG(ERROR) << "Cannot open " << path_ << std::endl;
    exit(1);
  }
  for (Document document : documents) {
    ofs << document.id << "\t" << document.title << "\t" << document.text
        << "\n";
  }
  ofs.close();
}
