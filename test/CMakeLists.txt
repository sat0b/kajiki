project(unitTests)

add_executable(xmlTest
        ${CMAKE_CURRENT_SOURCE_DIR}/XmlTest.cpp)

target_link_libraries(xmlTest
        XMLParser
        XMLTree
        gtest
        gtest_main
        pthread)

configure_file(xml/test.xml xml/test.xml)