cmake_minimum_required(VERSION 3.6)
project(lodepng)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.h)

add_library(lodepng ${SOURCE_FILES} ${HEADER_FILES})