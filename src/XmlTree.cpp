#include <iostream>
#include "XmlTree.h"

XmlTree::XmlTree(std::string tag, std::string text) : tag(tag), text(text) {}

XmlTree::XmlTree(std::multimap<std::string, XmlTree *> elements) : elements(elements) {}

std::vector<XmlTree *> XmlTree::find_all(std::string key) {
    auto itr = elements.find(key);
    std::vector<XmlTree *> xml_vec;
    while (itr != elements.end()) {
        xml_vec.push_back(itr->second);
        ++itr;
    }
    return xml_vec;
}

XmlTree *XmlTree::find(std::string key) {
    auto itr = elements.find(key);
    std::vector<XmlTree *> xml_vec;
    if (itr == elements.end())
        return nullptr;
    else
        return itr->second;
}

std::string XmlTree::get_text() {
    return text;
}

XmlTree::~XmlTree() {
    for (auto element : elements)
        delete element.second;
}

std::ostream &operator<<(std::ostream &os, const XmlTree &xml_tree) {
    for (auto element : xml_tree.elements) {
        std::string tag_name = element.first;
        XmlTree *child = element.second;
        os << "<" << tag_name;
        for (auto attr : element.second->attributes) {
            std::string attr_name = attr.first;
            std::string attr_value = attr.second;
            os << " " << attr_name << "=" << "\"" << attr_value << "\"";
        }
        os << ">";
        if (child->elements.empty())
            os << child->get_text();
        else
            os << *child;
        os << "</" << tag_name << ">";
    }
    return os;
}
