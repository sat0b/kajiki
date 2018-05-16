#ifndef KAJIKI_WIKIXMLPARSER_H
#define KAJIKI_WIKIXMLPARSER_H
#include <fstream>

// XML Parser Class for wikipedia XML format
class WikiXmlParser {
  public:
    explicit WikiXmlParser(std::string xml_name);

    void parse();

  private:
    std::ifstream xml_stream_;

    static std::string extract_tag_element(std::string page, std::string tag);
    std::string extract_page_tag();
    std::string read_tag();
    std::string read_element();
    char next();
    void back(int n);
};

#endif // KAJIKI_WIKIXMLPARSER_H
