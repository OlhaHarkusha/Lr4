add_library(MSTLib STATIC src/MSTLib.cpp)

target_include_directories(MSTLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MSTLib PUBLIC cxx_std_20)