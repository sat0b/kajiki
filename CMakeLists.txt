cmake_minimum_required(VERSION 3.9)
project(kajiki)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(src)
add_subdirectory(test)

include(CMakeModules/CodeCoverage.cmake)
setup_target_for_coverage(${PROJECT_NAME}_coverage tests coverage)

enable_testing()
add_test(NAME tokenizerTest COMMAND tokenizerTest)
add_test(NAME indexerTest COMMAND indexerTest)
add_test(NAME searcherTest COMMAND searcherTest)
add_test(NAME wikiXmlParserTest COMMAND wikiXmlParserTest)
