SET(SRC_LIST main.cpp server.cpp
             proto/build/request.pb.cc 
             proto/build/request.pb.h
             proto/build/httpRequest.pb.h
             proto/build/httpRequest.pb.cc)
            

# Find required protobuf package
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()

include_directories(/usr/local/protobuf/include/)
INCLUDE_DIRECTORIES(../include/)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -std=c++11 -g -ggdb")

#PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS proto/request.proto proto/httpRequest.proto)

#ADD_EXECUTABLE(tinyHttp ${SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS})
ADD_EXECUTABLE(tinyHttp ${SRC_LIST} )

target_link_libraries(tinyHttp protobuf pthread)
