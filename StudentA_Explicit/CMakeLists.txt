cmake_minimum_required(VERSION 3.20)
project(StudentA_Explicit LANGUAGES CXX)

add_executable(StudentA_Explicit main.cpp)

add_custom_command(TARGET StudentA_Explicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/DirGraphLib.dll"
        "$<TARGET_FILE_DIR:StudentA_Explicit>"
)