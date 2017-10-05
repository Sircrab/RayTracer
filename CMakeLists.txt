cmake_minimum_required(VERSION 3.6)
project(raytracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vec3.h Vec3.cpp lodepng/lodepng.cpp lodepng/lodepng.h cxxopts/cxxopts.hpp SceneParams.h SceneParams.cpp Vec4.h Vec4.cpp Ray.h Sphere.h Ray.cpp RenderParams.h Camera.h Camera.cpp Color.h Color.cpp Materials.h Lights.h SceneMaterials.h SceneMaterials.cpp SceneObject.h SceneObject.cpp Materials.cpp Parser.h Parser.cpp Renderer.h Renderer.cpp Lights.cpp Colorizer.h Colorizer.cpp Utils.cpp Utils.h Pixel.h SphereObject.h SphereObject.cpp RenderTask.h RenderTask.cpp RayCastHit.h Triangle.h Mesh.h MeshObject.h MeshObject.cpp Mesh.cpp Triangle.cpp AABB.h AABB.cpp Mat4x4.h Mat4x4.cpp Transform.h Mat3x3.h Mat3x3.cpp Transform.cpp OctreeNode.h Octree.h Octree.cpp)
add_executable(raytracer ${SOURCE_FILES})