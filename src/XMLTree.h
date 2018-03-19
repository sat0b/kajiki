#ifndef KAJIKI_XMLTREE_H
#define KAJIKI_XMLTREE_H

#include <string>
#include <map>

class XMLTree {
public:
    XMLTree() = default;
    std::string tag;
    std::string text;
    std::map<std::string, XMLTree *> elements;
};


#endif //KAJIKI_XMLTREE_H
