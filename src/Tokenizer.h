#ifndef KAJIKI_TOKENIZER_H
#define KAJIKI_TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer {
public:
    explicit Tokenizer(std::string text);
    std::vector<std::string> getBigram();

private:
    std::string nextUtf8Char();
    std::string readUtf8Char();
    size_t p;
    std::string text;
};


#endif //KAJIKI_TOKENIZER_H
