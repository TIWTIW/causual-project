cmake_minimum_required(VERSION 2.8)

project( logmodule )

SET(CMAKE_CXX_FLAGS "-std=c++0x")

set( SRC_LIST Myfunctions_test.cpp Myfunctions.cpp )

add_executable( test_myfunctions ${SRC_LIST})