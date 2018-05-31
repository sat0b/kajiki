#ifndef KAJIKI_DOCUMENT_H
#define KAJIKI_DOCUMENT_H

#include <string>

struct Document {
  int id;
  std::string title;
  std::string text;
  Document(int id, std::string title, std::string text)
      : id(id), title(title), text(text) {}
};

#endif // KAJIKI_DOCUMENT_H
