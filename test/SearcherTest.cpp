#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Searcher.h"
#include "../src/Indexer.h"

using ::testing::ElementsAre;

TEST(searcherTest, searcherTest) {
  std::vector<Document> documents;
  documents.emplace_back(1, "ab", "");
  documents.emplace_back(2, "abcd", "");
  documents.emplace_back(3, "cd", "");
  Indexer indexer(documents);
  std::map<std::string, std::vector<int>> postingList = indexer.getPostingList();
  Searcher searcher(postingList);
  ASSERT_THAT(searcher.search("ab"), ElementsAre(1, 2));
  ASSERT_THAT(searcher.search("cd"), ElementsAre(2, 3));
}

TEST(searcherTest, searcherInitializedByStorageIndex) {
  // output index
  std::vector<Document> documents;
  documents.emplace_back(1, "ab", "");
  documents.emplace_back(2, "abcd", "");
  documents.emplace_back(3, "cd", "");
  Indexer indexer(documents);
  indexer.outputStorage();

  // search
  Searcher searcher;
  searcher.loadIndex();
  ASSERT_THAT(searcher.search("ab"), ElementsAre(1, 2));
  ASSERT_THAT(searcher.search("cd"), ElementsAre(2, 3));
}