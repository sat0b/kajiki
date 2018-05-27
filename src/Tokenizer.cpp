#include "Tokenizer.h"

Tokenizer::Tokenizer(std::string text) : text(text), p(0) {}

std::vector<std::string> Tokenizer::getBigram() {
  std::vector<std::string> bigrams;
  std::string first;
  std::string second;
  while (p < text.length()) {
    first = nextUtf8Char();
    second = readUtf8Char();
    bigrams.push_back(first + second);
  }
  return bigrams;
}

std::string Tokenizer::nextUtf8Char() {
  std::string ret = readUtf8Char();
  p += ret.length();
  return ret;
}

std::string Tokenizer::readUtf8Char() {
  auto c0 = static_cast<unsigned char>(text[p]);
  auto c1 = static_cast<unsigned char>(text[p + 1]);

  if (0b00000000 <= c0 && c0 <= 0b01111111)
    return text.substr(p, 1);

  if (0b11000000 <= c0 && c0 <= 0b11011111 &&
      0b10000000 <= c1 && c1 <= 0b10111111)
    return text.substr(p, 2);

  if (0b11100000 <= c0 && c0 <= 0b11101111 &&
      0b10000000 <= c1 && c1 <= 0b10111111)
    return text.substr(p, 3);

  if (0b11110000 <= c0 && c0 <= 0b11110111 &&
      0b10000000 <= c1 && c1 <= 0b10111111)
    return text.substr(p, 4);

  return text.substr(p, 1);
}

