PROJECT(tinyHttp)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

ADD_SUBDIRECTORY( source )

