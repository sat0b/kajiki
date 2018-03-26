#include "Tokenizer.h"

Tokenizer::Tokenizer(std::string text) : text(text), p(0) {}

std::vector<std::string> Tokenizer::get_bigram() {
    std::vector<std::string> bigrams;
    std::string first;
    std::string second;
    while (p < text.length()) {
        first = next_utf8_char();
        second = read_utf8_char();
        bigrams.push_back(first + second);
    }
    return bigrams;
}

std::string Tokenizer::next_utf8_char() {
    std::string ret = read_utf8_char();
    p += ret.length();
    return ret;
}

std::string Tokenizer::read_utf8_char() {
    auto c0 = static_cast<unsigned char>(text[p]);
    auto c1 = static_cast<unsigned char>(text[p + 1]);
    if (0b00000000 <= c0 && c0 <= 0b01111111) {
        auto ret = text.substr(p, 1);
        return ret;
    }
    if (0b11000000 <= c0 && c0 <= 0b11011111 &&
        0b10000000 <= c1 && c1 <= 0b10111111) {
        auto ret = text.substr(p, 2);
        return ret;
    }
    if (0b11100000 <= c0 && c0 <= 0b11101111 &&
        0b10000000 <= c1 && c1 <= 0b10111111) {
        auto ret = text.substr(p, 3);
        return ret;
    }
    if (0b11110000 <= c0 && c0 <= 0b11110111 &&
        0b10000000 <= c1 && c1 <= 0b10111111) {
        auto ret = text.substr(p, 4);
        return ret;
    }
    auto ret = text.substr(p, 1);
    return ret;
}

