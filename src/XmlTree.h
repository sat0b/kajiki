#ifndef KAJIKI_XMLTREE_H
#define KAJIKI_XMLTREE_H

#include <string>
#include <map>
#include <vector>

class XmlTree {
public:
    XmlTree() = default;
    explicit XmlTree(std::multimap<std::string, XmlTree *> elements);
    XmlTree(std::string tag, std::string text);
    std::vector<XmlTree *> find_all(std::string key);
    XmlTree *find(std::string key);
    std::string tag;
    std::string text;
    std::multimap<std::string, XmlTree *> elements;
    std::map<std::string, std::string> attributes;
};

std::ostream &operator<<(std::ostream &os, const XmlTree &xml_tree);

#endif //KAJIKI_XMLTREE_H
