add_library(XMLParser STATIC XmlParser.cpp)
add_library(XMLTree STATIC XmlTree.cpp)

add_executable(${PROJECT_NAME}
        kajiki.cpp)

target_link_libraries(${PROJECT_NAME}
        XMLParser
        XMLTree)