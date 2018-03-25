#include <gtest/gtest.h>
#include "../src/Tokenizer.h"

TEST(tokenizer_tests, test1) {
    Tokenizer tokenizer(L"こんにちは世界");
    auto bigrams = tokenizer.get_bigram();
    EXPECT_EQ(L"こん", bigrams[0]);
    EXPECT_EQ(L"んに", bigrams[1]);
    EXPECT_EQ(L"にち", bigrams[2]);
    EXPECT_EQ(L"ちは", bigrams[3]);
    EXPECT_EQ(L"は世", bigrams[4]);
    EXPECT_EQ(L"世界", bigrams[5]);
}
