//
// Created by Geno on 21-Sep-17.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H
#include "Vec3.h"
#include "Ray.h"
#include "Triangle.h"
#include <limits>
#include <vector>

//Axis Aligned Bounding Box
class AABB{
public:
  Vec3 minVec, maxVec;
  std::vector<Vec3> boxVertices;
  AABB(Vec3 minVec, Vec3 maxVec) : minVec(minVec), maxVec(maxVec) {
    boxVertices.push_back(Vec3(minVec.x,minVec.y,minVec.z));
    boxVertices.push_back(Vec3(minVec.x,minVec.y,maxVec.z));
    boxVertices.push_back(Vec3(minVec.x,maxVec.y,minVec.z));
    boxVertices.push_back(Vec3(minVec.x,maxVec.y,maxVec.z));
    boxVertices.push_back(Vec3(maxVec.x,minVec.y,minVec.z));
    boxVertices.push_back(Vec3(maxVec.x,minVec.y,maxVec.z));
    boxVertices.push_back(Vec3(maxVec.x,maxVec.y,minVec.z));
    boxVertices.push_back(Vec3(maxVec.x,maxVec.y,maxVec.z));
  };
  bool intersect_ray(const Ray& ray) const;
  bool intersect_triangle(const std::vector<Vec3>& triVertices) const;
private:
  void project(const std::vector<Vec3>& points,const Vec3& projectionAxis, double& outMin, double& outMax) const;
};
#endif //RAYTRACER_AABB_H
