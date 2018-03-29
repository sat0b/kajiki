#ifndef KAJIKI_INDEXER_H
#define KAJIKI_INDEXER_H

#include <vector>
#include <map>
#include "Document.h"

class Indexer {
public:
    explicit Indexer(std::vector<Document> documents);
    void output();

private:
    std::vector<Document> documents;
    std::map<std::string, std::vector<int>> posting_list;
};

#endif //KAJIKI_INDEXER_H
