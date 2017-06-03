
cmake_minimum_required(VERSION 2.8)

project( Grid_Map_Core )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

set( GridCoreTest_SRC_LIST 
	 grid_map_core.cpp
	 test_GridMapCore.cpp
	)

add_executable( Test_GridMapCore ${GridCoreTest_SRC_LIST} )
target_link_libraries( Test_GridMapCore ${OpenCV_LIBS} )

set( test_GP_SRC_LIST
	 grid_map_core.cpp
	 GlobalPlanning.cpp
	 test_GP.cpp
	)

add_executable( test_GP ${test_GP_SRC_LIST} )
target_link_libraries( test_GP ${OpenCV_LIBS} )

set( test_COR_SRC_LIST
	 grid_map_coordinate.cpp
	 test_GridCoordinate.cpp
	)

add_executable( test_Coordinate ${test_COR_SRC_LIST} )
target_link_libraries( test_Coordinate ${OpenCV_LIBS} )
