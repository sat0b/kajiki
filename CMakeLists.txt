cmake_minimum_required(VERSION 3.9)
project(kajiki)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME xml_test COMMAND xml_test)
add_test(NAME tokenizer_test COMMAND tokenizer_test)
