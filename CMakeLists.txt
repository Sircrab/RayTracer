cmake_minimum_required(VERSION 3.6)
project(raytracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vec3.h Vec3.cpp lodepng/lodepng.cpp lodepng/lodepng.h cxxopts/cxxopts.hpp SceneParams.h SceneParams.cpp Vec4.h Vec4.cpp Ray.h Sphere.h Ray.cpp RenderParams.h Camera.h Camera.cpp Color.h Color.cpp Materials.h Lights.h SceneMaterials.h SceneMaterials.cpp SceneObject.h SceneObject.cpp Materials.cpp Parser.h Parser.cpp Renderer.h Renderer.cpp Lights.cpp Colorizer.h Colorizer.cpp Utils.cpp Utils.h Pixel.h)
add_executable(raytracer ${SOURCE_FILES})