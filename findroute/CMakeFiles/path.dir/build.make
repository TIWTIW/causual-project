# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/zhoufeitong/工程/findroute

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/zhoufeitong/工程/findroute

# Include any dependencies generated for this target.
include CMakeFiles/path.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/path.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/path.dir/flags.make

CMakeFiles/path.dir/main.cpp.o: CMakeFiles/path.dir/flags.make
CMakeFiles/path.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/zhoufeitong/工程/findroute/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/path.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/path.dir/main.cpp.o -c /media/zhoufeitong/工程/findroute/main.cpp

CMakeFiles/path.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/path.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/zhoufeitong/工程/findroute/main.cpp > CMakeFiles/path.dir/main.cpp.i

CMakeFiles/path.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/path.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/zhoufeitong/工程/findroute/main.cpp -o CMakeFiles/path.dir/main.cpp.s

CMakeFiles/path.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/path.dir/main.cpp.o.requires

CMakeFiles/path.dir/main.cpp.o.provides: CMakeFiles/path.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/path.dir/build.make CMakeFiles/path.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/path.dir/main.cpp.o.provides

CMakeFiles/path.dir/main.cpp.o.provides.build: CMakeFiles/path.dir/main.cpp.o


CMakeFiles/path.dir/box.cpp.o: CMakeFiles/path.dir/flags.make
CMakeFiles/path.dir/box.cpp.o: box.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/zhoufeitong/工程/findroute/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/path.dir/box.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/path.dir/box.cpp.o -c /media/zhoufeitong/工程/findroute/box.cpp

CMakeFiles/path.dir/box.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/path.dir/box.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/zhoufeitong/工程/findroute/box.cpp > CMakeFiles/path.dir/box.cpp.i

CMakeFiles/path.dir/box.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/path.dir/box.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/zhoufeitong/工程/findroute/box.cpp -o CMakeFiles/path.dir/box.cpp.s

CMakeFiles/path.dir/box.cpp.o.requires:

.PHONY : CMakeFiles/path.dir/box.cpp.o.requires

CMakeFiles/path.dir/box.cpp.o.provides: CMakeFiles/path.dir/box.cpp.o.requires
	$(MAKE) -f CMakeFiles/path.dir/build.make CMakeFiles/path.dir/box.cpp.o.provides.build
.PHONY : CMakeFiles/path.dir/box.cpp.o.provides

CMakeFiles/path.dir/box.cpp.o.provides.build: CMakeFiles/path.dir/box.cpp.o


CMakeFiles/path.dir/target.cpp.o: CMakeFiles/path.dir/flags.make
CMakeFiles/path.dir/target.cpp.o: target.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/zhoufeitong/工程/findroute/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/path.dir/target.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/path.dir/target.cpp.o -c /media/zhoufeitong/工程/findroute/target.cpp

CMakeFiles/path.dir/target.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/path.dir/target.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/zhoufeitong/工程/findroute/target.cpp > CMakeFiles/path.dir/target.cpp.i

CMakeFiles/path.dir/target.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/path.dir/target.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/zhoufeitong/工程/findroute/target.cpp -o CMakeFiles/path.dir/target.cpp.s

CMakeFiles/path.dir/target.cpp.o.requires:

.PHONY : CMakeFiles/path.dir/target.cpp.o.requires

CMakeFiles/path.dir/target.cpp.o.provides: CMakeFiles/path.dir/target.cpp.o.requires
	$(MAKE) -f CMakeFiles/path.dir/build.make CMakeFiles/path.dir/target.cpp.o.provides.build
.PHONY : CMakeFiles/path.dir/target.cpp.o.provides

CMakeFiles/path.dir/target.cpp.o.provides.build: CMakeFiles/path.dir/target.cpp.o


CMakeFiles/path.dir/func.cpp.o: CMakeFiles/path.dir/flags.make
CMakeFiles/path.dir/func.cpp.o: func.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/zhoufeitong/工程/findroute/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/path.dir/func.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/path.dir/func.cpp.o -c /media/zhoufeitong/工程/findroute/func.cpp

CMakeFiles/path.dir/func.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/path.dir/func.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/zhoufeitong/工程/findroute/func.cpp > CMakeFiles/path.dir/func.cpp.i

CMakeFiles/path.dir/func.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/path.dir/func.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/zhoufeitong/工程/findroute/func.cpp -o CMakeFiles/path.dir/func.cpp.s

CMakeFiles/path.dir/func.cpp.o.requires:

.PHONY : CMakeFiles/path.dir/func.cpp.o.requires

CMakeFiles/path.dir/func.cpp.o.provides: CMakeFiles/path.dir/func.cpp.o.requires
	$(MAKE) -f CMakeFiles/path.dir/build.make CMakeFiles/path.dir/func.cpp.o.provides.build
.PHONY : CMakeFiles/path.dir/func.cpp.o.provides

CMakeFiles/path.dir/func.cpp.o.provides.build: CMakeFiles/path.dir/func.cpp.o


CMakeFiles/path.dir/obstacle.cpp.o: CMakeFiles/path.dir/flags.make
CMakeFiles/path.dir/obstacle.cpp.o: obstacle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/zhoufeitong/工程/findroute/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/path.dir/obstacle.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/path.dir/obstacle.cpp.o -c /media/zhoufeitong/工程/findroute/obstacle.cpp

CMakeFiles/path.dir/obstacle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/path.dir/obstacle.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/zhoufeitong/工程/findroute/obstacle.cpp > CMakeFiles/path.dir/obstacle.cpp.i

CMakeFiles/path.dir/obstacle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/path.dir/obstacle.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/zhoufeitong/工程/findroute/obstacle.cpp -o CMakeFiles/path.dir/obstacle.cpp.s

CMakeFiles/path.dir/obstacle.cpp.o.requires:

.PHONY : CMakeFiles/path.dir/obstacle.cpp.o.requires

CMakeFiles/path.dir/obstacle.cpp.o.provides: CMakeFiles/path.dir/obstacle.cpp.o.requires
	$(MAKE) -f CMakeFiles/path.dir/build.make CMakeFiles/path.dir/obstacle.cpp.o.provides.build
.PHONY : CMakeFiles/path.dir/obstacle.cpp.o.provides

CMakeFiles/path.dir/obstacle.cpp.o.provides.build: CMakeFiles/path.dir/obstacle.cpp.o


# Object files for target path
path_OBJECTS = \
"CMakeFiles/path.dir/main.cpp.o" \
"CMakeFiles/path.dir/box.cpp.o" \
"CMakeFiles/path.dir/target.cpp.o" \
"CMakeFiles/path.dir/func.cpp.o" \
"CMakeFiles/path.dir/obstacle.cpp.o"

# External object files for target path
path_EXTERNAL_OBJECTS =

path: CMakeFiles/path.dir/main.cpp.o
path: CMakeFiles/path.dir/box.cpp.o
path: CMakeFiles/path.dir/target.cpp.o
path: CMakeFiles/path.dir/func.cpp.o
path: CMakeFiles/path.dir/obstacle.cpp.o
path: CMakeFiles/path.dir/build.make
path: /usr/local/lib/libopencv_videostab.so.2.4.9
path: /usr/local/lib/libopencv_ts.a
path: /usr/local/lib/libopencv_superres.so.2.4.9
path: /usr/local/lib/libopencv_stitching.so.2.4.9
path: /usr/local/lib/libopencv_contrib.so.2.4.9
path: /usr/local/lib/libopencv_nonfree.so.2.4.9
path: /usr/local/lib/libopencv_ocl.so.2.4.9
path: /usr/local/lib/libopencv_gpu.so.2.4.9
path: /usr/local/lib/libopencv_photo.so.2.4.9
path: /usr/local/lib/libopencv_objdetect.so.2.4.9
path: /usr/local/lib/libopencv_legacy.so.2.4.9
path: /usr/local/lib/libopencv_video.so.2.4.9
path: /usr/local/lib/libopencv_ml.so.2.4.9
path: /usr/local/lib/libopencv_calib3d.so.2.4.9
path: /usr/local/lib/libopencv_features2d.so.2.4.9
path: /usr/local/lib/libopencv_highgui.so.2.4.9
path: /usr/local/lib/libopencv_imgproc.so.2.4.9
path: /usr/local/lib/libopencv_flann.so.2.4.9
path: /usr/local/lib/libopencv_core.so.2.4.9
path: CMakeFiles/path.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/zhoufeitong/工程/findroute/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable path"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/path.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/path.dir/build: path

.PHONY : CMakeFiles/path.dir/build

CMakeFiles/path.dir/requires: CMakeFiles/path.dir/main.cpp.o.requires
CMakeFiles/path.dir/requires: CMakeFiles/path.dir/box.cpp.o.requires
CMakeFiles/path.dir/requires: CMakeFiles/path.dir/target.cpp.o.requires
CMakeFiles/path.dir/requires: CMakeFiles/path.dir/func.cpp.o.requires
CMakeFiles/path.dir/requires: CMakeFiles/path.dir/obstacle.cpp.o.requires

.PHONY : CMakeFiles/path.dir/requires

CMakeFiles/path.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/path.dir/cmake_clean.cmake
.PHONY : CMakeFiles/path.dir/clean

CMakeFiles/path.dir/depend:
	cd /media/zhoufeitong/工程/findroute && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/zhoufeitong/工程/findroute /media/zhoufeitong/工程/findroute /media/zhoufeitong/工程/findroute /media/zhoufeitong/工程/findroute /media/zhoufeitong/工程/findroute/CMakeFiles/path.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/path.dir/depend

