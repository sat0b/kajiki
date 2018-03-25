#include <iostream>
#include "XMLParser.h"
#include "XMLTree.h"

int main(int argc, char **argv) {
    XMLParser xml_parser;
    if (argc == 2) {
        std::string file_name = argv[1];
        xml_parser.open(file_name);
        XMLTree *root = xml_parser.parse();
        std::cout << *root << std::endl;
    }
}
