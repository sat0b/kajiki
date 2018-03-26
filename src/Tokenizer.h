#ifndef KAJIKI_TOKENIZER_H
#define KAJIKI_TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer {
public:
    explicit Tokenizer(std::string text);
    std::vector<std::string> get_bigram();

private:
    std::string next_utf8_char();
    std::string read_utf8_char();
    size_t p;
    std::string text;
};


#endif //KAJIKI_TOKENIZER_H
