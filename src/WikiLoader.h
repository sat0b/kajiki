#ifndef KAJIKI_WIKILOADER_H
#define KAJIKI_WIKILOADER_H

#include <vector>

class Document;
class XmlTree;

class WikiLoader {
public:
    explicit WikiLoader(XmlTree *xml_tree);
    ~WikiLoader();
    std::vector<Document> load();

private:
    XmlTree *xml_tree;
};


#endif //KAJIKI_WIKILOADER_H
