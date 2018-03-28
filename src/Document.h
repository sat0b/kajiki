#ifndef KAJIKI_DOCUMENT_H
#define KAJIKI_DOCUMENT_H


#include <string>

class Document {
public:
    Document(std::string title, std::string text);
    std::string to_string();
    std::string get_title();
    std::string get_text();

private:
    std::string title;
    std::string text;
};


#endif //KAJIKI_DOCUMENT_H
