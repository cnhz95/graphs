cmake_minimum_required(VERSION 3.24)
project(graphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(graphs main.cpp graph.cpp graph.h reader.cpp reader.h)
