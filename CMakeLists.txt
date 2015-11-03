cmake_minimum_required(VERSION 3.3)
project(ExtendedCal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp AST.h Lexer.h Lexer.cpp Parser.h Parser.cpp)
add_executable(ExtendedCal ${SOURCE_FILES})