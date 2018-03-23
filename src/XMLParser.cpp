#include <iostream>
#include "XMLParser.h"
#include "XMLTree.h"

XMLParser::XMLParser(std::string xml) :
        xml(xml), p(0) {}

XMLTree *XMLParser::parse() {
    auto root = new XMLTree;
    for (;;) {
        // read begin tag
        expect_skip('<');
        std::string tag;
        while (!(read() == ' ' || read() == '>'))
            tag += consume();
        // read attribute
        std::map<std::string, std::string> attrs = parse_attribute();
        expect_skip('>');
        std::string text = consume_until("</" + tag + ">");
        // read end tag
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
        for (auto attr : attrs)
            root->elements[tag]->attributes[attr.first] = attr.second;
        if (p == xml.length())
            break;
    }
    return root;
}

char XMLParser::consume() {
    return xml[p++];
}

char XMLParser::read() {
    return xml[p];
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

void XMLParser::skip_space() {
    while (p < xml.length()) {
        if (xml[p] == ' ' || xml[p] == '\t' || xml[p] == '\n')
            ++p;
        else
            break;
    }
}

bool XMLParser::skip(char c) {
    if (xml[p] != c)
        return false;
    ++p;
    return true;
}

std::map<std::string, std::string> XMLParser::parse_attribute() {
    std::map<std::string, std::string> attrs;
    if (read() == ' ') {
        while (read() != '>') {
            skip_space();
            std::string attrName = consume_until('=');
            expect_skip('=');
            std::string attrValue;
            expect_skip('"');
            while (read() != '"')
                attrValue += consume();
            expect_skip('"');
            attrs[attrName] = attrValue;
            skip_space();
        }
    }
    return attrs;
}
