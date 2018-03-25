#include <gtest/gtest.h>
#include "../src/XmlParser.h"
#include "../src/XmlTree.h"

TEST(unitTests, readSingleElementTag) {
    XmlParser xml_parser("<foo>bar</foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("foo", xml_tree->elements["foo"]->tag);
}

TEST(unitTests, readSingleElement) {
    XmlParser xml_parser("<foo>bar</foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("bar", xml_tree->elements["foo"]->text);
}

TEST(unitTests, readNestedElementText) {
    XmlParser xml_parser("<foo><bar>baz</bar></foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz", xml_tree->elements["foo"]->elements["bar"]->text);
}

TEST(unitTests, readNestedMultipleElement) {
    XmlParser xml_parser("<foo><bar1>baz1</bar1><bar2>baz2</bar2></foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz1", xml_tree->elements["foo"]->elements["bar1"]->text);
    EXPECT_EQ("baz2", xml_tree->elements["foo"]->elements["bar2"]->text);
}

TEST(unitTests, readAttribute) {
    XmlParser xml_parser("<foo attr=\"baz\">bar</foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz", xml_tree->elements["foo"]->attributes["attr"]);
}

TEST(unitTests, readMultipleAttribute) {
    XmlParser xml_parser("<foo attr=\"baz\"><bar attr1=\"a\" attr2=\"b\">baz</bar></foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("a", xml_tree->elements["foo"]->elements["bar"]->attributes["attr1"]);
    EXPECT_EQ("b", xml_tree->elements["foo"]->elements["bar"]->attributes["attr2"]);
}

TEST(unitTests, loadFile) {
    XmlParser xml_parser;
    xml_parser.open("test/xml/test.xml");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("Title", xml_tree->elements["page"]->elements["title"]->text);
    EXPECT_EQ("10", xml_tree->elements["page"]->elements["revision"]->elements["id"]->text);
}

TEST(unitTests, readAbbr) {
    XmlParser xml_parser("<text id=\"10\" bytes=\"150\" />");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("10", xml_tree->elements["text"]->attributes["id"]);
}

