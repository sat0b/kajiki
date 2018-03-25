#include <iostream>
#include "XmlTree.h"

XmlTree::XmlTree(std::string tag, std::string text) : tag(tag), text(text) {}

XmlTree::XmlTree(std::vector<XmlTree *> elements) : elements(elements) {}

XmlTree::XmlTree(std::string tag) : tag(tag) {}

XmlTree::XmlTree(std::string tag, std::map<std::string, std::string> attributes,
                 std::vector<XmlTree *> elements, std::string text)
        : tag(tag), elements(elements), attributes(attributes), text(text) {}

//std::ostream &operator<<(std::ostream &os, const XmlTree &xml_tree) {
//    for (auto element : xml_tree.elements) {
//        std::string tag_name = element.first;
//        XmlTree *child = element.second;
//        os << "<" << tag_name;
//        for (auto attr : element.second->attributes) {
//            std::string attr_name = attr.first;
//            std::string attr_value = attr.second;
//            os << " " << attr_name << "=" << "\"" << attr_value << "\"";
//        }
//        os << ">";
//        if (child->elements.empty())
//            os << child->text;
//        else
//            os << *child;
//        os << "</" << tag_name << ">";
//    }
//    return os;
//}
