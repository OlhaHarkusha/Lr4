cmake_minimum_required(VERSION 3.20)
project(DirGraphLibDLL LANGUAGES CXX)

add_library(DirGraphLib SHARED src/DirGraphLib.cpp)

target_compile_definitions(DirGraphLib PRIVATE DIRGRAPH_EXPORTS)

target_include_directories(DirGraphLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(DirGraphLib PUBLIC cxx_std_20)