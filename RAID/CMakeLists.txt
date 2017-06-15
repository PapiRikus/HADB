cmake_minimum_required(VERSION 3.6)
project(proyecto3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Almacenamiento.cpp Almacenamiento.h)
add_executable(proyecto3 ${SOURCE_FILES})