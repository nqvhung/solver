cmake_minimum_required(VERSION 3.5)
project(searching_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MonoFunction.h DPoint.cpp DPoint.h Max.h Sum.h CBPAlgo.h BruteForce.h Average.h Algo1.h Algo2.h)
add_executable(searching_cpp ${SOURCE_FILES})