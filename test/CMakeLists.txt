project(unitTests)

add_executable(unitTests
        Tests.cpp)

target_link_libraries(unitTests
        gtest
        gtest_main
        XMLTree
        XMLParser)
