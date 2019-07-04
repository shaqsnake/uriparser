cmake_minimum_required(VERSION 3.8)

set(This UriParser)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 11)

set(Headers
    include/uriparser/Uri.hpp
    src/UriPattern.hpp
)

set (Sources
    src/Uri.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${This} PUBLIC include)

add_subdirectory(test)
