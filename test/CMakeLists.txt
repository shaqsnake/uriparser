cmake_minimum_required(VERSION 3.8)

set(This UriTests)

set (Sources
    src/UriTests.cpp
    src/UriPctCoderTests.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Tests
)

target_include_directories(${This} PRIVATE ..)

target_link_libraries(${This} PUBLIC
    gtest_main
    UriParser
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
