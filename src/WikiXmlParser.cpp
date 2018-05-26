#include <iostream>
#include "WikiXmlParser.h"
#include <unistd.h>

WikiXmlParser::WikiXmlParser(std::string xmlName, int nDocument) :
    xmlStream_(xmlName), nDocument_(nDocument) {
    if (xmlStream_.fail()) {
        std::cerr << "Can't open file " << xmlName << std::endl;
        std::exit(1);
    }
}

std::vector<Document> WikiXmlParser::parseNext() {
    std::string page;
    int documentId = 0;
    std::vector<Document> documents;
    for (int i = 0; i < nDocument_; i++) {
        page = extractPageTag();
        if (page.length() == 0)
            break;
        std::string title = extractTagElement(page, "title");
        documents.emplace_back(documentId, title, "");
        ++documentId;
    }
    return documents;
}

std::string WikiXmlParser::extractTagElement(std::string page,
                                             std::string tag) {
    std::string beginTag = "<" + tag + ">";
    std::string endTag = "</" + tag + ">";
    size_t beginPos = page.find(beginTag) + beginTag.length();
    size_t length = page.find(endTag) - beginPos;
    return page.substr(beginPos, length);
}

std::string WikiXmlParser::extractPageTag() {
    std::string tag;
    // read beginning of page tag
    for (;;) {
        tag = readTag();
        if (tag == "")
            return "";
        if (tag == "page")
            break;
    }
    // read element of page tag
    std::string pageElement = readElement();
    return pageElement;
}

std::string WikiXmlParser::readTag() {
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

std::string WikiXmlParser::readElement() {
    std::string element;
    char c;
    while ((c = next()) != '\0') {
        if (c == '<') {
            // back to '<'
            back(1);
            std::string tag = readTag();
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
    if (xmlStream_.eof())
        return '\0';
    xmlStream_ >> c;
    return c;
}

void WikiXmlParser::back(int n) { xmlStream_.seekg(-n, std::ios_base::cur); }
