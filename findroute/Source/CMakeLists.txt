INCLUDE_DIRECTORIES( ../Include )

FIND_PACKAGE( OpenCV REQUIRED )

SET( SRC_LIST main.cpp
              box.cpp
              target.cpp
              func.cpp
              obstacle.cpp
              )

ADD_EXECUTABLE(path  main.cpp box.cpp target.cpp func.cpp obstacle.cpp)


TARGET_LINK_LIBRARIES(path ${OpenCV_LIBS})
