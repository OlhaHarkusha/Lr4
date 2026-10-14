cmake_minimum_required(VERSION 3.20)
project(StudentB_Implicit LANGUAGES CXX)

add_executable(StudentB_Implicit main.cpp)

target_include_directories(StudentB_Implicit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/MSTLib/include
)

target_link_libraries(StudentB_Implicit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/MSTLib/lib/MSTLib.lib
)

add_custom_command(TARGET StudentB_Implicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/MSTLib/bin/MSTLib.dll"
        "$<TARGET_FILE_DIR:StudentB_Implicit>"
)