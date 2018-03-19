#include <iostream>
#include "XMLParser.h"

XMLTree *XMLParser::parse(std::string xml) {
    auto root = new XMLTree;
    std::string tag;
    size_t p = 0;
    if (xml[p] == '<') {
        ++p;
        while (xml[p] != '>') {
            tag += xml[p];
            ++p;
        }
        root->tag = tag;
    }
    std::string text;
    ++p;
    while (xml[p] != '<') {
        text += xml[p];
        ++p;
    }
    root->text = text;
    if (xml[p] == '<' && xml[p+1] == '/') {
        p += 2;
    } else {
        std::cerr << "Parse error" << std::endl;
        exit(1);
    }
    std::string endTag;
    while (xml[p] != '>') {
        endTag += xml[p];
        ++p;
    }
    if (root->tag != endTag) {
        std::cerr << "Parse error" << std::endl;
        exit(1);
    }
    return root;
}