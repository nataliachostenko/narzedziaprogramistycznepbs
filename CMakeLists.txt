cmake_minimum_required(VERSION 3.10)
project(JNP1_4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(JNP1_4 main.cpp rebelfleet.h main.cpp imperialfleet.h battle.h)