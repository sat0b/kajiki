#include <gtest/gtest.h>
#include "../src/Tokenizer.h"

TEST(tokenizer_tests, test1) {
  Tokenizer tokenizer("こんにちは世界");
  auto bigrams = tokenizer.getBigram();
  EXPECT_EQ("こん", bigrams[0]);
  EXPECT_EQ("んに", bigrams[1]);
  EXPECT_EQ("にち", bigrams[2]);
  EXPECT_EQ("ちは", bigrams[3]);
  EXPECT_EQ("は世", bigrams[4]);
  EXPECT_EQ("世界", bigrams[5]);
}
