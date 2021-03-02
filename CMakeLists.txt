cmake_minimum_required(VERSION 3.10)
project(small-lang)

set(CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(small-lang
    "src/main.cc"
)

target_include_directories(small-lang PRIVATE "src/")
