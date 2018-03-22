#include <gtest/gtest.h>
#include "../src/XMLParser.h"
#include "../src/XMLTree.h"

TEST(unitTests, test1) {
    XMLParser xmlParser("<foo>bar</foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("foo", xmlTree->elements["foo"]->tag);
}

TEST(unitTests, test2) {
    XMLParser xmlParser("<foo>bar</foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("bar", xmlTree->elements["foo"]->text);
}

