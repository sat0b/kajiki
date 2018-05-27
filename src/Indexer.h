#ifndef KAJIKI_INDEXER_H
#define KAJIKI_INDEXER_H

#include <vector>
#include <map>
#include "Document.h"

class Indexer {
public:
  Indexer() = default;
  explicit Indexer(std::vector<Document> documents);
  void outputStorage();
  void readStorage();
  std::map<std::string, std::vector<int>> getPostingList();

private:
  const static std::string fileName;
  std::vector<Document> documents;
  std::map<std::string, std::vector<int>> postingList_;
  void makePostingList();
};

#endif //KAJIKI_INDEXER_H
