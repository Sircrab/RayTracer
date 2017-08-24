cmake_minimum_required(VERSION 3.6)
project(raytracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vec3.h Vec3.cpp lodepng/lodepng.cpp lodepng/lodepng.h cxxopts/cxxopts.hpp SceneParams.h SceneParams.cpp Vec4.h Vec4.cpp Ray.h Sphere.h Ray.cpp RenderParams.h Camera.h Camera.cpp Color.h Color.cpp)
add_executable(raytracer ${SOURCE_FILES})