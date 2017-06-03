cmake_minimum_required(VERSION 2.8)

project( logmodule )

SET(CMAKE_CXX_FLAGS "-std=c++0x")

set( SRC_LIST logmodule_test.cpp logmodule.cpp )

add_executable( test_logmodule ${SRC_LIST})