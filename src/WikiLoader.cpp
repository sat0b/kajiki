#include "WikiLoader.h"
#include "XmlTree.h"
#include "Document.h"

WikiLoader::WikiLoader(XmlTree *xml_tree) : xml_tree(xml_tree) {}

std::vector<Document> WikiLoader::load() {
    std::vector<Document> documents;
    for (auto page : xml_tree->find("mediawiki")->find_all("page")) {
        auto title = page->find("title");
        std::string dtitle;
        if (title != nullptr)
            dtitle = title->get_text();
        std::string dtext;
        auto revision = page->find("revision");
        if (revision != nullptr) {
            auto text = revision->find("text");
            dtext = text->get_text();
        }
        documents.emplace_back(dtitle, dtext);
    }
    return documents;
}

WikiLoader::~WikiLoader() {
    delete xml_tree;
}
