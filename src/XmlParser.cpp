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
    std::string tag;
    std::map<std::string, std::string> attributes;
    std::vector<XmlTree *> elements;
    std::string text;

    // read begin tag
    expect_skip('<');
    while (read() != ' ' && read() != '>' && read() != '/')
        tag += consume();
    // read attribute
    attributes = parse_attribute();
    // end tag abbreviation
    if (skip('/')) {
        expect_skip('>');
        return new XmlTree(tag, attributes, elements, text);
    }
    expect_skip('>');
    skip_space();
    text = consume_until("</" + tag + ">");
    // read end tag
    expect_skip('<');
    expect_skip('/');
    std::string end_tag = consume_until('>');
    expect_skip('>');

    elements = parse_elements(text);
    return new XmlTree(tag, attributes, elements, text);
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

std::vector<XmlTree *> XmlParser::parse_elements(std::string text) {
    std::vector<XmlTree *> elements;
    if (text.find('<') == std::string::npos)
        return elements;

    auto p = text.begin();
    while (p != text.end()) {
        // skip space
        while (*p == ' ' || *p == '\t' || *p == '\n')
            ++p;
        auto begin_p = p;
        if (*p != '<')
            parse_error("<");
        // read <
        ++p;
        std::string begin_tag;
        while (*p != '>' && *p != ' ') {
            begin_tag += *p;
            ++p;
        }
        // skip attribute
        if (*p == ' ') {
            while (*p != '>')
                ++p;
        }
        // read >
        ++p;
        // read end tag
        std::string rem_str = std::string(p, text.end());
        std::string end_tag = "</" + begin_tag + ">";
        size_t pos = rem_str.find(end_tag);
        if (pos == std::string::npos)
            parse_error("Not found " + end_tag + " in " + rem_str);
        p += pos + end_tag.length();
        // parse a element
        std::string sub_xml(begin_p, p);
        XmlParser xml_parser(sub_xml);
        XmlTree *element = xml_parser.parse();
        elements.push_back(element);
        // skip space
        while (*p == ' ' || *p == '\t' || *p == '\n')
            ++p;
    }
    return elements;
}

