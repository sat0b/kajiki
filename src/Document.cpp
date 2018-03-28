#include "Document.h"

Document::Document(std::string title, std::string text) :
        title(std::move(title)), text(std::move(text)) {}

std::string Document::to_string() {
    return title + ":" + text;
}

std::string Document::get_title() {
    return title;
}

std::string Document::get_text() {
    return text;
}
