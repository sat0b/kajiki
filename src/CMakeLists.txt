add_library(XMLParser STATIC XMLParser.cpp)
add_library(XMLTree STATIC XMLTree.cpp)

add_executable(${PROJECT_NAME}
        kajiki.cpp)

target_link_libraries(${PROJECT_NAME}
        XMLParser
        XMLTree)