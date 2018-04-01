#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Indexer.h"

using ::testing::ElementsAre;

TEST(indexer_test, posting_list) {
    std::vector<Document> documents;
    documents.emplace_back(1, "ab", "");
    documents.emplace_back(2, "abcd", "");
    documents.emplace_back(3, "cd", "");
    Indexer indexer(documents);
    std::map<std::string, std::vector<int>> posting_list = indexer.get_posting_list();
    ASSERT_THAT(posting_list["ab"], ElementsAre(1, 2));
    ASSERT_THAT(posting_list["cd"], ElementsAre(2, 3));
}
