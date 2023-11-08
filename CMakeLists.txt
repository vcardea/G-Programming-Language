cmake_minimum_required(VERSION 3.26)
project(G_Programming_Language)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/compiler)

add_executable(G_Programming_Language
        src/compiler/file.hpp
        src/compiler/main.cpp
        src/compiler/tokenizer.hpp)
