#include <iostream>
#include "XMLTree.h"

XMLTree::XMLTree(std::string tag, std::string text) : tag(tag), text(text) {}

std::ostream &operator<<(std::ostream &os, const XMLTree &xmlTree) {
    for (auto element : xmlTree.elements) {
        std::string tag_name = element.first;
        XMLTree *child = element.second;
        os << "<" << tag_name;
        for (auto attr : element.second->attributes) {
            std::string attr_name = attr.first;
            std::string attr_value = attr.second;
            os << " " << attr_name << "=" << "\"" << attr_value << "\"";
        }
        os << ">";
        if (child->elements.empty())
            os << child->text;
        else
            os << *child;
        os << "</" << tag_name << ">";
    }
    return os;
}
