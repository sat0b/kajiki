#ifndef KAJIKI_INDEXER_H
#define KAJIKI_INDEXER_H

#include <vector>
#include <map>
#include "Document.h"

class Indexer {
public:
    Indexer() = default;
    explicit Indexer(std::vector<Document> documents);
    std::map<std::string, std::vector<int>> getPostingList();
    void outputStorage();
    void readStorage();

private:
    const static std::string fileName;
    void makePostingList();
    std::vector<Document> documents;
    std::map<std::string, std::vector<int>> postingList_;
};

#endif //KAJIKI_INDEXER_H
