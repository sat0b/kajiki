add_library(Searcher STATIC Searcher.cpp)
add_library(Tokenizer STATIC Tokenizer.cpp)
add_library(Document STATIC Document.cpp)

add_library(Indexer STATIC Indexer.cpp)
target_link_libraries(Indexer INTERFACE Document)

add_library(WikiXmlParser STATIC WikiXmlParser.cpp)
target_link_libraries(WikiXmlParser INTERFACE Document)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        Searcher
        Tokenizer
        Document
        Indexer
        WikiXmlParser)