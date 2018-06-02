project(unitTests)

add_executable(tokenizerTest
        ${CMAKE_CURRENT_SOURCE_DIR}/TokenizerTest.cpp)
add_executable(indexerTest
        ${CMAKE_CURRENT_SOURCE_DIR}/IndexerTest.cpp)
add_executable(searcherTest
        ${CMAKE_CURRENT_SOURCE_DIR}/SearcherTest.cpp)
add_executable(wikiXmlParserTest
        ${CMAKE_CURRENT_SOURCE_DIR}/WikiXmlParserTest.cpp)

target_link_libraries(tokenizerTest libkajiki glog gmock gtest_main pthread)
target_link_libraries(indexerTest libkajiki glog gtest gmock gtest_main pthread)
target_link_libraries(searcherTest libkajiki glog gtest gmock gtest_main pthread)
target_link_libraries(wikiXmlParserTest libkajiki glog gtest gmock gtest_main pthread)

configure_file(xml/test.xml xml/test.xml)
