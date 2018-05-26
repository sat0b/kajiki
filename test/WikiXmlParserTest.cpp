#include "../src/WikiXmlParser.h"
#include <gtest/gtest.h>

TEST(wiki_xml_parser_test, xml_parse_test) {
    WikiXmlParser wikiXmlParser("test/xml/test.xml", 10);
    std::vector<Document> documents = wikiXmlParser.parseNext();
    ASSERT_EQ(documents.size(), 2);
    ASSERT_EQ(documents[0].title, "Title1");
    ASSERT_EQ(documents[1].title, "Title2");
}
