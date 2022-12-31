cmake_minimum_required(VERSION 3.24)
project(simplewindow C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2)
add_executable(simplewindow main.c)
