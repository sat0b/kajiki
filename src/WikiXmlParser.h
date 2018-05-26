#ifndef KAJIKI_WIKIXMLPARSER_H
#define KAJIKI_WIKIXMLPARSER_H
#include <fstream>
#include <vector>
#include "Document.h"

// XML Parser Class for Wikipedia XML format
class WikiXmlParser {
  public:
    WikiXmlParser(std::string xmlName, int nDocument);
    std::vector<Document> parseNext();

  private:
    int nDocument_;
    std::ifstream xmlStream_;

    static std::string extractTagElement(std::string page, std::string tag);
    std::string extractPageTag();
    std::string readTag();
    std::string readElement();
    char next();
    void back(int n);
};

#endif // KAJIKI_WIKIXMLPARSER_H
