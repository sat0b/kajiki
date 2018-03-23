project(unitTests)

add_executable(unitTests
        XMLTest.cpp)

target_link_libraries(unitTests
        XMLParser
        XMLTree
        gtest
        gtest_main
        pthread)
