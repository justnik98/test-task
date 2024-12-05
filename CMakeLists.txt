cmake_minimum_required(VERSION 3.30)
project(test_task)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_task main.cpp
        utils.cpp
        utils.h)
