#include <gtest/gtest.h>
#include "../src/XmlParser.h"
#include "../src/XmlTree.h"

TEST(xml_tests, read_single_element_tag) {
    XmlParser xml_parser("<foo>bar</foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("foo", xml_tree->find("foo")->tag);
}

TEST(xml_tests, read_single_element_tag_by_find_all) {
    XmlParser xml_parser("<foo>bar</foo>");
    XmlTree *xml_tree = xml_parser.parse();
    auto res = xml_tree->find_all("foo");
    EXPECT_EQ("foo", res[0]->tag);
}

TEST(xml_tests, read_single_element) {
    XmlParser xml_parser("<foo>bar</foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("bar", xml_tree->find("foo")->text);
}

TEST(xml_tests, read_nested_element_text) {
    XmlParser xml_parser("<foo><bar>baz</bar></foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz", xml_tree->find("foo")->find("bar")->text);
}

TEST(xml_tests, read_nested_multiple_element) {
    XmlParser xml_parser("<foo><bar1>baz1</bar1><bar2>baz2</bar2></foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz1", xml_tree->find("foo")->find("bar1")->text);
    EXPECT_EQ("baz2", xml_tree->find("foo")->find("bar2")->text);
}

TEST(xml_tests, read_attribute) {
    XmlParser xml_parser("<foo attr=\"baz\">bar</foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("baz", xml_tree->find("foo")->attributes["attr"]);
}

TEST(xml_tests, read_multiple_attribute) {
    XmlParser xml_parser("<foo attr=\"baz\"><bar attr1=\"a\" attr2=\"b\">baz</bar></foo>");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("a", xml_tree->find("foo")->find("bar")->attributes["attr1"]);
    EXPECT_EQ("b", xml_tree->find("foo")->find("bar")->attributes["attr2"]);
}

TEST(xml_tests, load_file) {
    XmlParser xml_parser;
    xml_parser.open("test/xml/test.xml");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("Title", xml_tree->find("page")->find("title")->text);
    EXPECT_EQ("10", xml_tree->find("page")->find("revision")->find("id")->text);
}

TEST(xml_tests, read_abbr) {
    XmlParser xml_parser("<text id=\"10\" bytes=\"150\" />");
    XmlTree *xml_tree = xml_parser.parse();
    EXPECT_EQ("10", xml_tree->find("text")->attributes["id"]);
}

TEST(xml_tests, read_duplicated_element) {
    XmlParser xml_parser("<foo><bar>baz1</bar><bar>baz2</bar></foo>");
    XmlTree *xml_tree = xml_parser.parse();
    auto res = xml_tree->find("foo")->find_all("bar");
    EXPECT_EQ("baz1", res[0]->text);
    EXPECT_EQ("baz2", res[1]->text);
}
