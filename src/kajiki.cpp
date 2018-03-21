#include <iostream>
#include "XMLParser.h"

int main() {
    XMLParser xmlParser("<foo>bar</foo>");
    XMLTree *root = xmlParser.parse();
}
