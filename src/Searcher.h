#ifndef KAJIKI_SEARCHER_H
#define KAJIKI_SEARCHER_H

#include <map>
#include <vector>

class Searcher {
public:
    explicit Searcher();
    explicit Searcher(std::map<std::string, std::vector<int>> postingList);
    std::vector<int> search(std::string query);

private:
    std::map<std::string, std::vector<int>> postingList_;
};


#endif //KAJIKI_SEARCHER_H
