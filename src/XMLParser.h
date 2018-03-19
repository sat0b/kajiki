#ifndef KAJIKI_XMLPARSER_H
#define KAJIKI_XMLPARSER_H

#include "XMLTree.h"

class XMLParser {
public:
    XMLTree *parse(std::string xml);
};

#endif //KAJIKI_XMLPARSER_H
