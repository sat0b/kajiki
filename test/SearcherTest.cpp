#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Searcher.h"
#include "../src/Indexer.h"

using ::testing::ElementsAre;

TEST(seacher_test, searcher_test) {
    std::vector<Document> documents;
    documents.emplace_back(1, "ab", "");
    documents.emplace_back(2, "abcd", "");
    documents.emplace_back(3, "cd", "");
    Indexer indexer(documents);
    std::map<std::string, std::vector<int>> posting_list = indexer.get_posting_list();
    Searcher searcher(posting_list);
    ASSERT_THAT(searcher.search("ab"), ElementsAre(1, 2));
    ASSERT_THAT(searcher.search("cd"), ElementsAre(2, 3));
}

TEST(seacher_test, searcher_initialized_by_storage_index) {
    // output index
    std::vector<Document> documents;
    documents.emplace_back(1, "ab", "");
    documents.emplace_back(2, "abcd", "");
    documents.emplace_back(3, "cd", "");
    Indexer indexer(documents);
    indexer.output_storage();

    // search
    Searcher searcher;
    ASSERT_THAT(searcher.search("ab"), ElementsAre(1, 2));
    ASSERT_THAT(searcher.search("cd"), ElementsAre(2, 3));
}