cmake_minimum_required(VERSION 3.20)
project(StudentA_Implicit LANGUAGES CXX)

add_executable(StudentA_Implicit main.cpp)

target_include_directories(StudentA_Implicit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/DirGraphLib/include
)

target_link_libraries(StudentA_Implicit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/DirGraphLib/lib/DirGraphLib.lib
)

add_custom_command(TARGET StudentA_Implicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/DirGraphLib/bin/DirGraphLib.dll"
        "$<TARGET_FILE_DIR:StudentA_Implicit>"
)