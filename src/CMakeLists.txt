add_library(Searcher STATIC Searcher.cpp)
add_library(Tokenizer STATIC Tokenizer.cpp)
add_library(Indexer STATIC Indexer.cpp)
add_library(Dictionary STATIC Dictionary.cpp)
add_library(WikiXmlParser STATIC WikiXmlParser.cpp)
add_library(Server STATIC Server.cpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        Searcher
        Tokenizer
        Indexer
        WikiXmlParser
        Dictionary
        Server)