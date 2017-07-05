INCLUDE_DIRECTORIES( ../Includes )

FIND_PACKAGE( OpenCV REQUIRED )

SET( SRC_LIST main.cpp
              Map.cpp
              function.cpp
              ETree.cpp
              )

SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
add_compile_options(-g)

ADD_EXECUTABLE(path  ${SRC_LIST})

TARGET_LINK_LIBRARIES(path ${OpenCV_LIBS})
