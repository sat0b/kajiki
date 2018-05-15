#include "../src/WikiXmlParser.h"
#include <gtest/gtest.h>

TEST(wiki_xml_parser_test, test1) {
    WikiXmlParser wiki_xml_parser("xml/test.xml");
    wiki_xml_parser.parse();
}
