project(unitTests)

add_executable(unitTests
        Tests.cpp)

target_link_libraries(unitTests
        XMLTree
        XMLParser
        gtest
        gtest_main
        pthread)
