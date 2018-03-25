project(unitTests)

add_executable(xml_test
        ${CMAKE_CURRENT_SOURCE_DIR}/XmlTest.cpp)

target_link_libraries(xml_test
        XmlParser
        XmlTree
        gtest
        gtest_main
        pthread)

configure_file(xml/test.xml xml/test.xml)