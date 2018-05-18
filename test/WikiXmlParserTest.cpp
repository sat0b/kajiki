#include "../src/WikiXmlParser.h"
#include <gtest/gtest.h>

TEST(wiki_xml_parser_test, xml_parse_test) {
    WikiXmlParser wiki_xml_parser("xml/test.xml");
    wiki_xml_parser.parse();
}
