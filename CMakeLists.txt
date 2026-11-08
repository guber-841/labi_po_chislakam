cmake_minimum_required(VERSION 3.16)

project(laba06 LANGUAGES CXX)

add_executable( laba 
    source/main.cpp
    source/functions.cpp
)

target_compile_features(laba PRIVATE cxx_std_20)

target_include_directories(laba PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/source/headers"
)

set_target_properties(laba PROPERTIES CXX_EXTENSIONS OFF)