add_library(XmlParser STATIC XmlParser.cpp)
add_library(XmlTree STATIC XmlTree.cpp)
add_library(Searcher STATIC Searcher.cpp)
add_library(Tokenizer STATIC Tokenizer.cpp)
add_library(Document STATIC Document.cpp)
add_library(WikiLoader STATIC WikiLoader.cpp)
add_library(Indexer STATIC Indexer.cpp)

add_executable(${PROJECT_NAME}
        main.cpp)

target_link_libraries(${PROJECT_NAME}
        XmlParser
        XmlTree
        Indexer
        Tokenizer
        WikiLoader
        Document
        Searcher)