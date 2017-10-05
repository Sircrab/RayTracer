//
// Created by Geno on 20-Sep-17.
//
#include "MeshObject.h"
#include <limits>
bool MeshObject::intersect_ray(const Ray &ray, RayCastHit &out) const {
  if(!boundingBox.intersect_ray(ray)) return false;
  if(octree.maxDepth == 0){
    return intersect_mesh(ray, out);
  }
  return intersect_recursive(ray, out, octree.root, 0);
}

bool MeshObject::intersect_mesh(const Ray &ray, RayCastHit &out) const {
  double minDistance = std::numeric_limits<double>::max();
  bool hit = false;
  for(int i = 0 ; i < mesh->triangles.size(); i++){
    RayCastHit innerRayCast;
    bool curHit = mesh->triangles[i].intersect_ray(ray, mesh, innerRayCast);
    if(curHit && (innerRayCast.hitPos - ray.origin).magnitude() < minDistance){
      hit |= curHit;
      minDistance = (innerRayCast.hitPos - ray.origin).magnitude();
      out = innerRayCast;
    }
  }
  return hit;
}

bool MeshObject::intersect_recursive(const Ray &ray, RayCastHit &out, std::shared_ptr<OctreeNode> curNode,
                                     unsigned int curDepth) const{
  bool hit = false;
  double minDistance = std::numeric_limits<double>::max();
  if(curDepth < octree.maxDepth){
    for(auto& childNode: curNode->children){
      if(childNode->boundingBox.intersect_ray(ray)){
        hit |= intersect_recursive(ray, out, childNode, curDepth+1);
        if((out.hitPos - ray.origin).magnitude() < minDistance){
          minDistance = (out.hitPos - ray.origin).magnitude();
        }
      }
    }
    return hit;
  }
  for(int i = 0 ; i < curNode->tris.size(); i++){
    RayCastHit innerHit;
    bool curHit = mesh->triangles[curNode->tris[i]].intersect_ray(ray, mesh, innerHit);
    if(curHit && (innerHit.hitPos - ray.origin).magnitude() < minDistance){
      hit |= curHit;
      minDistance = (innerHit.hitPos - ray.origin).magnitude();
      out = innerHit;
    }
  }
  return hit;
}
