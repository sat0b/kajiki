cmake_minimum_required(VERSION 3.9)
project(kajiki)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_subdirectory(src)
add_subdirectory(test)

include(CMakeModules/CodeCoverage.cmake)
setup_target_for_coverage(${PROJECT_NAME}_coverage tests coverage)

enable_testing()
add_test(NAME xml_test COMMAND xml_test)
add_test(NAME tokenizer_test COMMAND tokenizer_test)
add_test(NAME wikiloader_test COMMAND wikiloader_test)
add_test(NAME indexer_test COMMAND indexer_test)
add_test(NAME searcher_test COMMAND searcher_test)
