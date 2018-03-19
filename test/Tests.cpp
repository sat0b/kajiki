#include <gtest/gtest.h>
#include "../src/XMLParser.h"

TEST(unitTests, test1) {
    XMLParser xmlParser;
    XMLTree *xmlTree = xmlParser.parse("<foo>bar</foo>");
    EXPECT_EQ("foo", xmlTree->tag);
}

TEST(unitTests, test2) {
    XMLParser xmlParser;
    XMLTree *xmlTree = xmlParser.parse("<foo>bar</foo>");
    EXPECT_EQ("bar", xmlTree->text);
}
