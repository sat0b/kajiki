add_library(libkajiki STATIC
    Searcher.cpp
    Tokenizer.cpp
    Indexer.cpp
    Dictionary.cpp
    WikiXmlParser.cpp
    Server.cpp
    )

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} libkajiki glog)
