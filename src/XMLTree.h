#ifndef KAJIKI_XMLTREE_H
#define KAJIKI_XMLTREE_H

#include <string>
#include <map>

class XMLTree {
public:
    XMLTree() = default;
    XMLTree(std::string tag, std::string text);
    std::string tag;
    std::string text;
    std::map<std::string, XMLTree *> elements;
    std::map<std::string, std::string> attributes;
};

#endif //KAJIKI_XMLTREE_H
