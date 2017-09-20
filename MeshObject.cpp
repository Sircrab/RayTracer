//
// Created by Geno on 20-Sep-17.
//
#include "MeshObject.h"
#include <limits>
bool MeshObject::intersect_ray(const Ray &ray, RayCastHit &out) const {
  double minDistance = std::numeric_limits<double>::max();
  bool hit = false;
  for(int i = 0 ; i < mesh.triangles.size(); i++){
    RayCastHit innerRayCast;
    bool curHit = mesh.triangles[i].intersect_ray(ray, mesh, innerRayCast);
    if(curHit && (innerRayCast.hitPos - ray.origin).magnitude() < minDistance){
      hit |= curHit;
      minDistance = (innerRayCast.hitPos - ray.origin).magnitude();
      out = innerRayCast;
    }
  }
  return hit;
}