//
// Created by Geno on 20-Sep-17.
//

#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H
#include "Vec3.h"
#include "Triangle.h"
#include <vector>
#include <string>
class AABB; //forward declaration
class Mesh {
public:
  std::vector<Vec3> vertices;
  std::vector<Vec3> normals;
  std::vector<Triangle> triangles;
  Mesh(){};
  void parse_from_file(const std::string& file, bool computeNormals);
  AABB calc_AABB();
private:
  void parse_vertex_line(const std::string& line);
  void parse_normal_line(const std::string& line);
  void parse_uv_line(const std::string& line);
  void parse_face_line(const std::string& line, bool computeNormals);
};
#endif //RAYTRACER_MESH_H
