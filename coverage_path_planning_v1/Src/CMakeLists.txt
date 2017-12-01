INCLUDE_DIRECTORIES( ../Inc )

FIND_PACKAGE( OpenCV REQUIRED )

SET( SRC_LIST main.cpp
              map.cpp
              obstacle.cpp
              robot.cpp
              )

ADD_EXECUTABLE(coverage_path ${SRC_LIST})

TARGET_LINK_LIBRARIES(coverage_path ${OpenCV_LIBS})
