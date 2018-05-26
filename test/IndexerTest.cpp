#include <sys/stat.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Indexer.h"

using ::testing::ElementsAre;

TEST(indexerTest, postingListTest) {
    std::vector<Document> documents;
    documents.emplace_back(1, "ab", "");
    documents.emplace_back(2, "abcd", "");
    documents.emplace_back(3, "cd", "");
    Indexer indexer(documents);
    std::map<std::string, std::vector<int>> postingList = indexer.getPostingList();
    ASSERT_THAT(postingList["ab"], ElementsAre(1, 2));
    ASSERT_THAT(postingList["cd"], ElementsAre(2, 3));
}

TEST(indexerTest, indexerOutputTest) {
    std::vector<Document> documents;
    documents.emplace_back(1, "ab", "");
    documents.emplace_back(2, "abcd", "");
    documents.emplace_back(3, "cd", "");
    Indexer indexer(documents);
    indexer.outputStorage();
    struct stat buffer;
    ASSERT_TRUE(stat("/tmp/kajiki.index", &buffer) == 0);
}


TEST(indexerTest, indexerReadTest) {
    Indexer indexer;
    indexer.readStorage();
    std::map<std::string, std::vector<int>> postingList = indexer.getPostingList();
    ASSERT_THAT(postingList["ab"], ElementsAre(1, 2));
    ASSERT_THAT(postingList["cd"], ElementsAre(2, 3));
}