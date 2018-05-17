project(unitTests)

add_executable(tokenizer_test
        ${CMAKE_CURRENT_SOURCE_DIR}/TokenizerTest.cpp)
add_executable(indexer_test
        ${CMAKE_CURRENT_SOURCE_DIR}/IndexerTest.cpp)
add_executable(searcher_test
        ${CMAKE_CURRENT_SOURCE_DIR}/SearcherTest.cpp)
add_executable(wiki_xml_parser_test
        ${CMAKE_CURRENT_SOURCE_DIR}/WikiXmlParserTest.cpp)

target_link_libraries(tokenizer_test
        Tokenizer
        gtest
        gtest_main
        pthread)

target_link_libraries(indexer_test
        Indexer
        Tokenizer
        Document
        gtest
        gmock
        gtest_main
        pthread)

target_link_libraries(searcher_test
        Searcher
        Tokenizer
        Indexer
        Document
        gtest
        gtest_main
        pthread)

target_link_libraries(wiki_xml_parser_test
        Document
        WikiXmlParser
        gtest
        gtest_main
        pthread)

configure_file(xml/test.xml xml/test.xml)