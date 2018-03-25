#include <iostream>
#include <fstream>
#include "XmlParser.h"
#include "XmlTree.h"

XmlParser::XmlParser() : p(0) {}

XmlParser::XmlParser(std::string xml) :
        xml(xml), p(0) {}

void XmlParser::open(std::string file_name) {
    std::ifstream fin(file_name);
    if (fin.fail())
        parse_error("Not found " + file_name);
    std::istreambuf_iterator<char> it(fin);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);
    xml = str;
}

XmlTree *XmlParser::parse() {
    std::multimap<std::string, XmlTree *> elements;
    while (p < xml.length()) {
        skip_space();
        // read begin tag
        expect_skip('<');
        // skip xml declaration
        if (skip('?')) {
            consume_until("?>");
            expect_skip('?');
            expect_skip('>');
            continue;
        }
        std::string tag;
        while (read() != ' ' && read() != '>' && read() != '/')
            tag += consume();
        // read attribute
        std::map<std::string, std::string> attrs = parse_attribute();
        // end tag abbreviation
        if (skip('/')) {
            expect_skip('>');
            auto child = new XmlTree;
            for (auto attr : attrs)
                child->attributes[attr.first] = attr.second;
            auto element = std::make_pair(tag, child);
            elements.insert(element);
            skip_space();
            continue;
        }
        expect_skip('>');
        skip_space();
        std::string text = consume_until("</" + tag + ">");
        // read end tag
        expect_skip('<');
        expect_skip('/');
        std::string end_tag = consume_until('>');
        expect_skip('>');
        if (tag != end_tag)
            parse_error("Not found end tag, " + tag);
        XmlTree *child;
        if (text.find('<') == std::string::npos) {
            child = new XmlTree(tag, text);
        } else {
            auto child_parser = new XmlParser(text);
            child = child_parser->parse();
        }
        for (auto attr : attrs)
            child->attributes[attr.first] = attr.second;
        auto element = std::make_pair(tag, child);
        elements.insert(element);
        skip_space();
    }
    return new XmlTree(elements);
}

char XmlParser::consume() {
    return xml[p++];
}

char XmlParser::read() {
    return xml[p];
}

std::string XmlParser::consume_until(char c) {
    std::string res;
    while (xml[p] != c) {
        res += consume();
    }
    return res;
}

std::string XmlParser::consume_until(std::string str) {
    std::string rem_str = xml.substr(p);
    size_t s = rem_str.find(str);
    if (s == std::string::npos)
        parse_error("Not found " + str + " in " + rem_str);
    p += s;
    return rem_str.substr(0, s);
}

void XmlParser::expect_skip(char c) {
    std::string msg;
    if (xml[p] != c) {
        msg += c + " expected : " + xml[p];
        parse_error(msg);
    }
    next();
}

void XmlParser::parse_error(std::string msg) {
    std::cerr << "Parse error " + msg << std::endl;
    std::exit(1);
}

void XmlParser::skip_space() {
    while (p < xml.length()) {
        if (xml[p] == ' ' || xml[p] == '\t' || xml[p] == '\n')
            next();
        else
            break;
    }
}

void XmlParser::next() {
    ++p;
}

bool XmlParser::skip(char c) {
    if (xml[p] != c)
        return false;
    next();
    return true;
}

std::map<std::string, std::string> XmlParser::parse_attribute() {
    std::map<std::string, std::string> attrs;
    if (read() == ' ') {
        while (read() != '>' && read() != '/') {
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

