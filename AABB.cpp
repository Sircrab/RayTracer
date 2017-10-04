//
// Created by Geno on 21-Sep-17.
//
#include "AABB.h"

bool AABB::intersect_ray(const Ray &ray) const{
  double tMin, tMax, tYMin, tYMax, tZMin, tZMax, t;
  Vec3 invDir = Vec3(1.0,1.0,1.0) / ray.direction;
  bool xSign = invDir.x < 0; // 1 is negative 0 is positive
  bool ySign = invDir.y < 0;
  bool zSign = invDir.z < 0;
  tMin = ((xSign ? maxVec.x : minVec.x) - ray.origin.x) * invDir.x;
  tMax = ((!xSign ? maxVec.x : minVec.x) - ray.origin.x) * invDir.x;
  tYMin = ((ySign ? maxVec.y : minVec.y) - ray.origin.y) * invDir.y;
  tYMax = ((!ySign ? maxVec.y : minVec.y) - ray.origin.y) * invDir.y;

  if((tMin > tYMax) || (tYMin > tMax)) return false;
  if(tYMin > tMin){
    tMin = tYMin;
  }
  if(tYMax < tMax){
    tMax = tYMax;
  }

  tZMin = ((zSign ? maxVec.z : minVec.z) - ray.origin.z) * invDir.z;
  tZMax = ((!zSign ? maxVec.z : minVec.z) - ray.origin.z) * invDir.z;

  if(tZMin > tMin){
    tMin = tZMin;
  }
  if(tZMax < tMax){
    tMax = tZMax;
  }
  t = tMin;
  if(t < 0){
    t = tMax;
    if(t < 0) return false;
  }
  return true;
}
//Based on stackoverflow answer:
// https://stackoverflow.com/questions/17458562/efficient-aabb-triangle-intersection-in-c-sharp
bool AABB::intersect_triangle(const std::vector<Vec3>& triVertices) const {
  double triangleMin = 0;
  double triangleMax = 0;
  double boxMin = 0;
  double boxMax = 0;
  std::vector<Vec3> boxNormals = {Vec3(1,0,0),Vec3(0,1,0),Vec3(0,0,1)};
  for (int i = 0 ; i < 3; i++){
    project(triVertices, boxNormals[i], triangleMin, triangleMax);
    if(triangleMax < minVec[i] || triangleMin > maxVec[i]) return false;
  }
  Vec3 triNormal = (triVertices[1]-triVertices[0]).cross(triVertices[2]-triVertices[0]).normalize();
  double triOffset = triNormal.dot(triVertices[0]);
  project(boxVertices, triNormal, boxMin, boxMax);
  if(boxMax < triOffset || boxMin > triOffset) return false;
  std::vector<Vec3> triEdges = {triVertices[0]-triVertices[1],
                                triVertices[1] - triVertices[2],
                                triVertices[2] - triVertices[0]};
  for(int i = 0 ; i < 3; i++){
    for(int j = 0; j < 3; j++){
      Vec3 axis = triEdges[i].cross(boxNormals[j]);
      project(boxVertices, axis, boxMin, boxMax);
      project(triVertices, axis, triangleMin, triangleMax);
      if(boxMax < triangleMin || boxMin > triangleMax) return false;
    }
  }
  return true;
}

void AABB::project(const std::vector<Vec3>& points,const Vec3& projectionAxis, double &outMin, double &outMax) const{
  outMin = std::numeric_limits<double>::max();
  outMax = std::numeric_limits<double>::min();
  for(const auto& p : points){
    double val = projectionAxis.dot(p);
    outMin = std::min(val, outMin);
    outMax = std::min(val, outMax);
  }
}
