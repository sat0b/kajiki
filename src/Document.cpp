#include "Document.h"

Document::Document(int document_id, std::string title, std::string text) :
    document_id(document_id), title(std::move(title)), text(std::move(text)) {}

std::string Document::to_string() {
    return title + ":" + text;
}

std::string Document::get_title() {
    return title;
}

std::string Document::get_text() {
    return text;
}

int Document::get_id() {
    return document_id;
}
