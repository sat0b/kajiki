add_library(XmlParser STATIC XmlParser.cpp)
add_library(XmlTree STATIC XmlTree.cpp)
add_library(Searcher STATIC Searcher.cpp)
add_library(Tokenizer STATIC Tokenizer.cpp)

add_executable(${PROJECT_NAME}
        kajiki.cpp)

target_link_libraries(${PROJECT_NAME}
        XmlParser
        XmlTree)