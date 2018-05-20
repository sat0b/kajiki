#ifndef KAJIKI_WIKIXMLPARSER_H
#define KAJIKI_WIKIXMLPARSER_H
#include <fstream>
#include <vector>
#include "Document.h"

// XML Parser Class for Wikipedia XML format
class WikiXmlParser {
  public:
    WikiXmlParser(std::string xml_name, int n_document);
    std::vector<Document> parse_next();

  private:
    int n_document_;
    std::ifstream xml_stream_;

    static std::string extract_tag_element(std::string page, std::string tag);
    std::string extract_page_tag();
    std::string read_tag();
    std::string read_element();
    char next();
    void back(int n);
};

#endif // KAJIKI_WIKIXMLPARSER_H
