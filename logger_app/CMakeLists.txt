cmake_minimum_required(VERSION 2.6)
project(logger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

include_directories(../logger)

link_directories(../logger)
add_definitions(-D_DEBUG)
add_executable(logger_app source/main.cpp)

target_link_libraries(logger_app logger)




