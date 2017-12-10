######################################################
# 这是tinySTL项目根目录下的CMakeLists.txt
# 
######################################################

# CMake 版本要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project( zft_tinySTL )
set(Demo_VERSION_MAJOR 3)
set(Demo_VERSION_MINOR 0)

# 设置编译输出目录:可执行程序放在bin目录下，动态链接库放在lib目录下
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 添加编译条件
add_compile_options(-std=c++11)

# 添加项目头文件搜索目录
include_directories( ./Include )

# 添加项目源文件目录，注意要在每个源文件目录下添加CMakeLists.txt
add_subdirectory( ${PROJECT_SOURCE_DIR}/Source )

