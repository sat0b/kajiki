#include "Tokenizer.h"

Tokenizer::Tokenizer(std::wstring text) : text(text) {}

std::vector<std::wstring> Tokenizer::get_bigram() {
    std::vector<std::wstring> bigrams;
    for (size_t i = 0; i < text.length() - 1; i++)
        bigrams.push_back(text.substr(i, 2));
    return bigrams;
}
