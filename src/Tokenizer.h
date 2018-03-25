#ifndef KAJIKI_TOKENIZER_H
#define KAJIKI_TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer {
public:
    explicit Tokenizer(std::wstring text);
    std::vector<std::wstring> get_bigram();
public:
    std::wstring text;
};


#endif //KAJIKI_TOKENIZER_H
