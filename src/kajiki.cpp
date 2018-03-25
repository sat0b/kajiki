#include <iostream>
#include "XmlParser.h"
#include "XmlTree.h"

int main(int argc, char **argv) {
    XmlParser xml_parser;
    if (argc == 2) {
        std::string file_name = argv[1];
        xml_parser.open(file_name);
        XmlTree *root = xml_parser.parse();
    }
}
