//
// Created by Geno on 21-Sep-17.
//
#include "AABB.h"
//Based on https://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/
bool AABB::intersect_ray(const Ray &ray) const{

  double tx1 = (minVec.x - ray.origin.x) * ray.invDir.x;
  double tx2 = (maxVec.x - ray.origin.x) * ray.invDir.x;
  double ty1 = (minVec.y - ray.origin.y) * ray.invDir.y;
  double ty2 = (maxVec.y - ray.origin.y) * ray.invDir.y;
  double tz1 = (minVec.z - ray.origin.z) * ray.invDir.z;
  double tz2 = (maxVec.z - ray.origin.z) * ray.invDir.z;

  double tmin = std::max(std::max(std::min(tx1,tx2), std::min(ty1,ty2)), std::min(tz1, tz2));
  double tmax = std::min(std::min(std::max(tx1,tx2), std::max(ty1,ty2)), std::max(tz1, tz2));
  if(tmax < 0 || tmin > tmax){
    return false;
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
  Vec3 triNormal = (triVertices[1]-triVertices[0]).cross(triVertices[2]-triVertices[0]);
  double triOffset = triNormal.dot(triVertices[0]);
  project(boxVertices, triNormal, boxMin, boxMax);
  if(boxMax < triOffset || boxMin > triOffset) return false;
  std::vector<Vec3> triEdges = {triVertices[0] - triVertices[1],
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
    outMax = std::max(val, outMax);
  }
}
