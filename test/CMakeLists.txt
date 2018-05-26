project(unitTests)

add_executable(tokenizerTest
        ${CMAKE_CURRENT_SOURCE_DIR}/TokenizerTest.cpp)
add_executable(indexerTest
        ${CMAKE_CURRENT_SOURCE_DIR}/IndexerTest.cpp)
add_executable(searcherTest
        ${CMAKE_CURRENT_SOURCE_DIR}/SearcherTest.cpp)
add_executable(wikiXmlParserTest
        ${CMAKE_CURRENT_SOURCE_DIR}/WikiXmlParserTest.cpp)

target_link_libraries(tokenizerTest Tokenizer gtest gmock gtest_main pthread)
target_link_libraries(indexerTest Indexer Tokenizer gtest gmock gtest_main pthread)
target_link_libraries(searcherTest Searcher Indexer Tokenizer gtest gmock gtest_main pthread)
target_link_libraries(wikiXmlParserTest WikiXmlParser gtest gmock gtest_main pthread)

configure_file(xml/test.xml xml/test.xml)