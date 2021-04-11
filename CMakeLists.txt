cmake_minimum_required(VERSION 3.17)
project(pycones2014_kata C)

set(CMAKE_C_STANDARD 99)

# Add an library for the production classes
add_library(lib
        lib.c
        lib.cpp lib.h)

add_executable(exe
        main.c
        )

target_link_libraries(exe
        lib
        )

add_subdirectory(tests)