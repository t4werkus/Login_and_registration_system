cmake_minimum_required(VERSION 3.24)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled1 main.cpp ../untitled/library.cpp library.cpp test.cpp test.cpp)
