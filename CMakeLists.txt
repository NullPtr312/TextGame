cmake_minimum_required(VERSION 3.20)

project(main)

file(GLOB SOURCE_FILES "src/core/*" "src/management/*" "src/objects/*" "src/main.cpp")
add_executable(main ${SOURCE_FILES})

target_include_directories(main PUBLIC include)

