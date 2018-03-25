#ifndef KAJIKI_XMLTREE_H
#define KAJIKI_XMLTREE_H

#include <string>
#include <map>

class XmlTree {
public:
    XmlTree() = default;
    XmlTree(std::string tag, std::string text);
    std::string tag;
    std::string text;
    std::map<std::string, XmlTree *> elements;
    std::map<std::string, std::string> attributes;
};

std::ostream &operator<<(std::ostream &os, const XmlTree &xml_tree);

#endif //KAJIKI_XMLTREE_H
