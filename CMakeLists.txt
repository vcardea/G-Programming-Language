cmake_minimum_required(VERSION 3.26)
project(G_Programming_Language)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/compiler)

add_executable(G_Programming_Language
        src/file.hpp
        src/compile.cpp
        src/tokenizer.hpp
        src/utils.hpp)
