cmake_minimum_required(VERSION 3.20)
project(MSTLibDLL LANGUAGES CXX)

add_library(MSTLib SHARED src/MSTLib.cpp)

target_compile_definitions(MSTLib PRIVATE MSTLIB_EXPORTS)

target_include_directories(MSTLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MSTLib PUBLIC cxx_std_20)