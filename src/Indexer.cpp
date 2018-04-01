#include <iostream>
#include <fstream>
#include <sstream>
#include "Indexer.h"
#include "Tokenizer.h"


Indexer::Indexer(std::vector<Document> documents) : documents(documents) {
    make_posting_list();
}

void Indexer::make_posting_list() {
    for (Document document : documents) {
        std::string title = document.get_title();
        int document_id = document.get_id();
        Tokenizer tokenizer(title);
        std::vector<std::string> bigrams = tokenizer.get_bigram();
        for (std::string index : bigrams) {
            posting_list[index].push_back(document_id);
        }
    }
}

std::map<std::string, std::vector<int>> Indexer::get_posting_list() {
    return posting_list;
}

void Indexer::output_storage() {
    std::string file_name = "/tmp/kajiki.index";
    std::ofstream ofs(file_name, std::ios::out);
    if (!ofs.is_open()) {
        std::cerr << "Cannot open /tmp/kajiki.index" << std::endl;
        exit(1);
    }
    for (auto posting : posting_list) {
        std::string index = posting.first;
        ofs << index << "\t";
        for (int document_id : posting.second)
            ofs << document_id << "\t";
        ofs << std::endl;
    }
    ofs.close();
}

void Indexer::read_storage() {
    std::string file_name = "/tmp/kajiki.index";
    char delimiter = '\t';
    std::ifstream ifs(file_name, std::ios::in);
    if (!ifs.is_open()) {
        std::cerr << "Not found /tmp/kajiki.index" << std::endl;
        exit(1);
    }
    std::string line;
    while (getline(ifs, line)) {
        std::istringstream ss(line);
        std::string index;
        std::getline(ss, index, delimiter);
        std::string col;
        while (std::getline(ss, col, delimiter)) {
            int document_id = std::stoi(col);
            posting_list[index].push_back(document_id);
        }
    }
    ifs.close();
}
