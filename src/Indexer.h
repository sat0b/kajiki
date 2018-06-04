#ifndef KAJIKI_INDEXER_H
#define KAJIKI_INDEXER_H

#include "Document.h"
#include <map>
#include <vector>

class Indexer {
public:
  Indexer() = default;
  explicit Indexer(std::vector<Document> documents);
  void outputStorage();
  void readStorage();
  std::map<std::string, std::vector<int>> getPostingList();

private:
  const static std::string filename;
  std::vector<Document> documents_;
  std::map<std::string, std::vector<int>> postingList_;
  void makePostingList();
};

#endif // KAJIKI_INDEXER_H
