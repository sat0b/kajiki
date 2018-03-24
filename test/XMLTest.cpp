#include <gtest/gtest.h>
#include "../src/XMLParser.h"
#include "../src/XMLTree.h"

TEST(unitTests, readSingleElementTag) {
    XMLParser xmlParser("<foo>bar</foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("foo", xmlTree->elements["foo"]->tag);
}

TEST(unitTests, readSingleElement) {
    XMLParser xmlParser("<foo>bar</foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("bar", xmlTree->elements["foo"]->text);
}

TEST(unitTests, readNestedElementText) {
    XMLParser xmlParser("<foo><bar>baz</bar></foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("baz", xmlTree->elements["foo"]->elements["bar"]->text);
}

TEST(unitTests, readNestedMultipleElement) {
    XMLParser xmlParser("<foo><bar1>baz1</bar1><bar2>baz2</bar2></foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("baz1", xmlTree->elements["foo"]->elements["bar1"]->text);
    EXPECT_EQ("baz2", xmlTree->elements["foo"]->elements["bar2"]->text);
}

TEST(unitTests, readAttribute) {
    XMLParser xmlParser("<foo attr=\"baz\">bar</foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("baz", xmlTree->elements["foo"]->attributes["attr"]);
}

TEST(unitTests, readMultipleAttribute) {
    XMLParser xmlParser("<foo attr=\"baz\"><bar attr1=\"a\" attr2=\"b\">baz</bar></foo>");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("a", xmlTree->elements["foo"]->elements["bar"]->attributes["attr1"]);
    EXPECT_EQ("b", xmlTree->elements["foo"]->elements["bar"]->attributes["attr2"]);
}

TEST(unitTests, loadFile) {
    XMLParser xmlParser;
    xmlParser.open("test/xml/test.xml");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("Title", xmlTree->elements["page"]->elements["title"]->text);
    EXPECT_EQ("10", xmlTree->elements["page"]->elements["revision"]->elements["id"]->text);
}

TEST(unitTests, readAbbr) {
    XMLParser xmlParser("<text id=\"10\" bytes=\"150\" />");
    XMLTree *xmlTree = xmlParser.parse();
    EXPECT_EQ("10", xmlTree->elements["text"]->attributes["id"]);
}
