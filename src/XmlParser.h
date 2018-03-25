#ifndef KAJIKI_XMLPARSER_H
#define KAJIKI_XMLPARSER_H

#include <map>

class XmlTree;

class XmlParser {
public:
    XmlParser();
    XmlParser(std::string xml);
    XmlTree *parse();
    void open(std::string file_name);

private:
    size_t p;
    std::string xml;
    bool skip(char c);
    void skip_space();
    void expect_skip(char c);
    void parse_error(std::string msg);
    char consume();
    char read();
    void next();
    std::map<std::string, std::string> parse_attribute();
    std::string consume_until(char c);
    std::string consume_until(std::string str);
};

#endif //KAJIKI_XMLPARSER_H
