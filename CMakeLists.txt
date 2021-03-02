cmake_minimum_required(VERSION 3.10)
project(small-lang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(small-lang
    "src/main.cc"
)

target_include_directories(small-lang PRIVATE "src/")
