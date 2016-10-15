cmake_minimum_required(VERSION 2.6)
project (test)


set(CMAKE_VERBOSE_MAKEFILE ON)


message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")


add_executable(main main.cpp)
#add_executable(main Tom3112.cpp)

target_link_libraries(main sfml-graphics sfml-window sfml-system)
