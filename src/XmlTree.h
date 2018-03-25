#ifndef KAJIKI_XMLTREE_H
#define KAJIKI_XMLTREE_H

#include <string>
#include <map>
#include <vector>

class XmlTree {
public:
    XmlTree() = default;
    explicit XmlTree(std::vector<XmlTree *> elements);
    explicit XmlTree(std::string tag);
    XmlTree(std::string tag, std::map<std::string, std::string> attributes,
            std::vector<XmlTree *> elements, std::string text);
    XmlTree(std::string tag, std::string text);
    std::string tag;
    std::string text;
    std::vector<XmlTree *> elements;
    std::map<std::string, std::string> attributes;
};

std::ostream &operator<<(std::ostream &os, const XmlTree &xml_tree);

#endif //KAJIKI_XMLTREE_H
