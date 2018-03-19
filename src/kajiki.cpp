#include <iostream>
#include "XMLParser.h"

int main() {
    XMLParser xmlParser;
    XMLTree *root = xmlParser.parse("<foo>bar</foo>");
}
