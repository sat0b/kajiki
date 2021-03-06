#ifndef KAJIKI_DICTIONARY_H
#define KAJIKI_DICTIONARY_H

#include "Document.h"
#include <map>
#include <vector>

class Dictionary {
public:
  explicit Dictionary(std::string path);
  ~Dictionary();
  std::vector<Document> readAll(std::vector<int> documentIds);
  void putAll(std::vector<Document> documents);

private:
  std::string path_;
  std::map<int, Document> dict_;
};

#endif // KAJIKI_DICTIONARY_H
