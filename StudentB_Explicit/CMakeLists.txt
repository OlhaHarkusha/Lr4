cmake_minimum_required(VERSION 3.20)
project(StudentB_Explicit LANGUAGES CXX)

# ─────────────────────────────────────────────────────────────
# 1. Створюємо виконуваний файл.
#    НІЯКИХ target_include_directories і target_link_libraries —
#    ми не підключаємо ні .h, ні .lib!
# ─────────────────────────────────────────────────────────────
add_executable(StudentB_Explicit main.cpp)

# ─────────────────────────────────────────────────────────────
# 2. Копіюємо .dll поруч із .exe після збірки,
#    щоб LoadLibrary міг її знайти за відносним шляхом.
# ─────────────────────────────────────────────────────────────
add_custom_command(TARGET StudentB_Explicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/MSTLib.dll"
        "$<TARGET_FILE_DIR:StudentB_Explicit>"
    COMMENT "Copy MSTLib.dll next to StudentB_Explicit.exe"
)