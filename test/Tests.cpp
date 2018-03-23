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

TEST(unitTests, test3) {
    XMLParser xmlParser("<foo><bar>baz</bar></foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("baz", xmlTree->elements["foo"]->elements["bar"]->text);
}

TEST(unitTests, test4) {
    XMLParser xmlParser("<foo><bar1>baz1</bar1><bar2>baz2</bar2></foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("baz1", xmlTree->elements["foo"]->elements["bar1"]->text);
    EXPECT_EQ("baz2", xmlTree->elements["foo"]->elements["bar2"]->text);
}
