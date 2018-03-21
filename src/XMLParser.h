#ifndef KAJIKI_XMLPARSER_H
#define KAJIKI_XMLPARSER_H

#include "XMLTree.h"

class XMLParser {
public:
    XMLParser(std::string xml);
    XMLTree *parse();
    void expect_skip(char c);
    void parse_error(std::string msg);
    char consume();
    std::string consume_until(char c);
    std::string consume_until(std::string str);

private:
    size_t p;
    std::string xml;
};

#endif //KAJIKI_XMLPARSER_H
