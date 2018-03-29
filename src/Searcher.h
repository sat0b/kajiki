#ifndef KAJIKI_SEARCHER_H
#define KAJIKI_SEARCHER_H

#include "XmlTree.h"

class Searcher {
public:
    Searcher(std::map<std::string, std::vector<int>> posting_list);
    std::vector<int> search(std::string query);

private:
    std::map<std::string, std::vector<int>> posting_list;
};


#endif //KAJIKI_SEARCHER_H
