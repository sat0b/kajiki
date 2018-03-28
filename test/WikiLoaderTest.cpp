#include <gtest/gtest.h>
#include "../src/WikiLoader.h"
#include "../src/Document.h"
#include "../src/XmlTree.h"
#include "../src/XmlParser.h"

TEST(wiki_loader_tests, load_wiki) {
    std::string xml = R"(
<mediawiki>
  <page>
    <title>テストタイトル</title>
    <revision>
      <text>テストテキスト</text>
    </revision>
  </page>
  <page>
    <title>テストタイトル2</title>
    <revision>
      <text>テストテキスト2</text>
    </revision>
  </page>
</mediawiki>
)";
    XmlParser xml_parser(xml);
    XmlTree *xml_tree = xml_parser.parse();
    WikiLoader wiki_loader(xml_tree);
    std::vector<Document> documents = wiki_loader.load();
    EXPECT_EQ(2, documents.size());
    EXPECT_EQ("テストタイトル", documents[0].get_title());
    EXPECT_EQ("テストテキスト", documents[0].get_text());
    EXPECT_EQ("テストタイトル2", documents[1].get_title());
    EXPECT_EQ("テストテキスト2", documents[1].get_text());
}
