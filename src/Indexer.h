#ifndef KAJIKI_INDEXER_H
#define KAJIKI_INDEXER_H

#include <vector>
#include <map>
#include "Document.h"

class Indexer {
public:
    Indexer() = default;
    explicit Indexer(std::vector<Document> documents);
    std::map<std::string, std::vector<int>> get_posting_list();
    void output_storage();
    void read_storage();

private:
    void make_posting_list();
    std::vector<Document> documents;
    std::map<std::string, std::vector<int>> posting_list;
};

#endif //KAJIKI_INDEXER_H
