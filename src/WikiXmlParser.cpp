#include "WikiXmlParser.h"
#include <iostream>

WikiXmlParser::WikiXmlParser(std::string xml_name) : xml_stream_(xml_name) {}

void WikiXmlParser::parse() {
    std::string page;
    for (;;) {
        page = extract_page_tag();
        if (page.length() == 0)
            break;
        std::cout << page << "\n";
        std::cout << "title:" << WikiXmlParser::extract_tag_element(page, "title") << "\n";
        std::cout << "id:" << WikiXmlParser::extract_tag_element(page, "id") << "\n";

    }
}

std::string WikiXmlParser::extract_tag_element(std::string page, std::string tag) {
    std::string begin_tag = "<" + tag + ">";
    std::string end_tag = "</" + tag + ">";
    int begin_pos = page.find(begin_tag) + begin_tag.length();
    int end_pos = page.find(end_tag) - begin_pos;
    std::string title_element = page.substr(begin_pos, end_pos);
    return title_element;
}

std::string WikiXmlParser::extract_page_tag() {
    std::string tag;
    // read beginning of page tag
    for (;;) {
        tag = read_tag();
        if (tag == "")
            return "";
        if (tag == "page")
            break;
    }
    // read element of page tag
    std::string page_element = read_element();

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
        if (c == '<') {
            // back to '<'
            back(1);
            std::string tag = read_tag();
            if (tag == "/page")
                break;
            element += '<' + tag + '>';
        } else {
            element += c;
        }
    }
    return element;
}

char WikiXmlParser::next() {
    char c;
    if (xml_stream_.eof())
        return '\0';
    xml_stream_ >> c;
    return c;
}

void WikiXmlParser::back(int n) { xml_stream_.seekg(-n, std::ios_base::cur); }
