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
