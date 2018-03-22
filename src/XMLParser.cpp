#include <iostream>
#include "XMLParser.h"
#include "XMLTree.h"

XMLParser::XMLParser(std::string xml) :
        xml(xml), p(0) {}

XMLTree *XMLParser::parse() {
    auto root = new XMLTree;
    expect_skip('<');
    std::string tag = consume_until('>');
    expect_skip('>');
    std::string text = consume_until("</" + tag + ">");
    expect_skip('<');
    expect_skip('/');
    std::string endTag = consume_until('>');
    expect_skip('>');
    if (tag != endTag)
        parse_error("Not found end tag, " + tag);
    if (text.find('<') == std::string::npos) {
        root->elements[tag] = new XMLTree(tag, text);
    } else {
        auto child = new XMLParser(text);
        root->elements[tag] = child->parse();
    }
    return root;
}

char XMLParser::consume() {
    return xml[p++];
}

std::string XMLParser::consume_until(char c) {
    std::string res;
    while (xml[p] != c) {
        res += consume();
    }
    return res;
}

std::string XMLParser::consume_until(std::string str) {
    std::string remStr = xml.substr(p);
    size_t s = remStr.find(str);
    if (s == std::string::npos)
        parse_error("Not found " + str + " in " + remStr);
    p += s;
    return remStr.substr(0, s);
}

void XMLParser::expect_skip(char c) {
    std::string msg;
    if (xml[p] != c) {
        msg += c + " expected : " + xml[p];
        parse_error(msg);
    }
    ++p;
}

void XMLParser::parse_error(std::string msg) {
    std::cerr << "Parse error " + msg << std::endl;
    std::exit(1);
}
