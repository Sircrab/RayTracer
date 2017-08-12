cmake_minimum_required(VERSION 3.6)
project(raytracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vec3.h Vec3.cpp lodepng/lodepng.cpp lodepng/lodepng.h SceneParams.h SceneParams.cpp Vec4.h Vec4.cpp)
add_executable(raytracer ${SOURCE_FILES})