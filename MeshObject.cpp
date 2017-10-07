//
// Created by Geno on 20-Sep-17.
//
#include "MeshObject.h"
#include <limits>
#include <iostream>

bool MeshObject::intersect_ray(const Ray &ray, RayCastHit &out) const {
  if(octree.maxDepth == 0){
    return intersect_mesh(ray, out);
  } else {
    std::unordered_set<unsigned int> triSet;
    std::vector<AABB> aabbs;
    intersect_recursive(ray, triSet, octree.root, 0, aabbs);
    /*
    if(triSet.size() > 1000){
      std::cout << "--------------" << std::endl;
      std::cout << triSet.size() << std::endl;
      std::cout << "Ray Origin: " << ray.origin.to_string() << " Direction: " << ray.direction.to_string() << std::endl;
      for(auto box : aabbs){
        std::cout << "Box start: " << box.minVec.to_string() << " End: " << box.maxVec.to_string() << std::endl;
      }
    }*/
    double minDistance = std::numeric_limits<double>::max();
    bool hit = false;
    for(auto triIdx : triSet){
      RayCastHit innerRayHit;
      bool curHit = mesh->triangles[triIdx].intersect_ray(ray, mesh,innerRayHit);
      if(curHit && (innerRayHit.hitPos - ray.origin).magnitude() < minDistance){
        hit |= curHit;
        minDistance = (innerRayHit.hitPos - ray.origin).magnitude();
        out = innerRayHit;
      }
    }
    return hit;
  }

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

void MeshObject::intersect_recursive(const Ray &ray, std::unordered_set<unsigned int>& triSet, std::shared_ptr<OctreeNode> curNode,
                                     unsigned int curDepth, std::vector<AABB>& aabbs) const{
  if(!curNode->boundingBox.intersect_ray(ray)){
    return;
  } else {
    if(curDepth < (octree.maxDepth - 1)){
      for(auto& childNode : curNode->children){
        intersect_recursive(ray, triSet, childNode, curDepth + 1, aabbs);
      }
    } else {
      for(auto triIdx : curNode->tris){
        triSet.insert(triIdx);
      }
      aabbs.push_back(curNode->boundingBox);
    }
  }
}
