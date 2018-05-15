#include <iostream>
#include "WikiXmlParser.h"

WikiXmlParser::WikiXmlParser(std::string xml_name) : xml_stream_(xml_name) {}

void WikiXmlParser::parse() {
    std::string page;
    for (;;) {
        page = extract_page_tag();
        if (page.length() == 0)
            break;
        std::cout << page << "\n";
    }
}

std::string WikiXmlParser::extract_page_tag() {
    std::string tag;
    // read beginning of page tag
    for (;;) {
        tag = read_tag();
        if (tag == "page")
            break;
    }

    // read element of page tag
    std::string page_element = read_element();

    // read end of page tag
    for (;;) {
        tag = read_tag();
        if (tag == "/page")
            break;
    }

    return page_element;
}

std::string WikiXmlParser::read_tag() {
    std::string tag;
    char c;
    while ((c = next()) != '\0') {
        if (c == '<')
            break;
    }
    while ((c = next()) != '\0') {
        if (c == '>')
            break;
        tag += c;
    }
    return tag;
}

std::string WikiXmlParser::read_element() {
    std::string element;
    char c;
    while ((c = next()) != '\0') {
        if (c == '<')
            break;
        element += c;
    }
    // back to '<'
    xml_stream_.seekg(-1, std::ios_base::cur);
    return element;
}

char WikiXmlParser::next() {
    char c;
    if (xml_stream_.eof())
        return '\0';
    xml_stream_ >> c;
    return c;
}
