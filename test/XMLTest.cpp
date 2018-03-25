#include <gtest/gtest.h>
#include "../src/XMLParser.h"
#include "../src/XMLTree.h"

TEST(unitTests, readSingleElementTag) {
    XMLParser xml_parser("<foo>bar</foo>");
    XMLTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("foo", xml_tree->elements["foo"]->tag);
}

TEST(unitTests, readSingleElement) {
    XMLParser xml_parser("<foo>bar</foo>");
    XMLTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("bar", xml_tree->elements["foo"]->text);
}

TEST(unitTests, readNestedElementText) {
    XMLParser xml_parser("<foo><bar>baz</bar></foo>");
    XMLTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz", xml_tree->elements["foo"]->elements["bar"]->text);
}

TEST(unitTests, readNestedMultipleElement) {
    XMLParser xml_parser("<foo><bar1>baz1</bar1><bar2>baz2</bar2></foo>");
    XMLTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz1", xml_tree->elements["foo"]->elements["bar1"]->text);
    EXPECT_EQ("baz2", xml_tree->elements["foo"]->elements["bar2"]->text);
}

TEST(unitTests, readAttribute) {
    XMLParser xml_parser("<foo attr=\"baz\">bar</foo>");
    XMLTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz", xml_tree->elements["foo"]->attributes["attr"]);
}

TEST(unitTests, readMultipleAttribute) {
    XMLParser xml_parser("<foo attr=\"baz\"><bar attr1=\"a\" attr2=\"b\">baz</bar></foo>");
    XMLTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("a", xml_tree->elements["foo"]->elements["bar"]->attributes["attr1"]);
    EXPECT_EQ("b", xml_tree->elements["foo"]->elements["bar"]->attributes["attr2"]);
}

TEST(unitTests, loadFile) {
    XMLParser xml_parser;
    xml_parser.open("test/xml/test.xml");
    XMLTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("Title", xml_tree->elements["page"]->elements["title"]->text);
    EXPECT_EQ("10", xml_tree->elements["page"]->elements["revision"]->elements["id"]->text);
}

TEST(unitTests, readAbbr) {
    XMLParser xml_parser("<text id=\"10\" bytes=\"150\" />");
    XMLTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("10", xml_tree->elements["text"]->attributes["id"]);
}

