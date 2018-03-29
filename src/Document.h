#ifndef KAJIKI_DOCUMENT_H
#define KAJIKI_DOCUMENT_H


#include <string>

class Document {
public:
    Document(int document_id, std::string title, std::string text);
    std::string to_string();
    std::string get_title();
    std::string get_text();
    int get_id();

private:
    std::string title;
    std::string text;
    int document_id;
};


#endif //KAJIKI_DOCUMENT_H
