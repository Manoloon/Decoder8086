cmake_minimum_required(VERSION 3.20)
project(Decoder8086)

set(CMAKE_CXX_STANDARD 17)

add_executable(Decoder8086 main.cpp
    Disassemble8080/8080.cpp)
