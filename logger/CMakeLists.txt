cmake_minimum_required(VERSION 2.6)
project(logger)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-D_DEBG)
add_library(logger logger.cpp)


