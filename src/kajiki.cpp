#include <iostream>
#include "XMLParser.h"

int main(int argc, char **argv) {
    XMLParser xmlParser;
    if (argc == 2) {
        std::string fileName = argv[1];
        xmlParser.open(fileName);
        XMLTree *root = xmlParser.parse();
    }
}
