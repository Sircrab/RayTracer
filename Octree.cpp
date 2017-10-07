//
// Created by Geno on 04-Oct-17.
//
#include <iostream>
#include "Octree.h"

void Octree::build(const std::shared_ptr<Mesh> mesh) {
  if(maxDepth > 0){
    build_root(mesh);
    build_recursive(0, root, mesh);
  }
}

void Octree::build_root(const std::shared_ptr<Mesh> mesh) {
  root = std::make_shared<OctreeNode>();
  root->boundingBox = mesh->calc_AABB();
  root->depth = 0;
  std::vector<unsigned int> trisIdxs;
  for(unsigned int i = 0 ; i < mesh->triangles.size(); i++){
    root->tris.push_back(i);
  }
}

void Octree::build_recursive(unsigned int curDepth, std::shared_ptr<OctreeNode> curNode, std::shared_ptr<Mesh> mesh) {
  if(curDepth >= (maxDepth - 1)) return;
  std::vector<AABB> childBoxes = generate_octants(curNode->boundingBox);
  for(int i = 0 ; i < 8; i++){
    curNode->children.push_back(std::make_shared<OctreeNode>(childBoxes[i],curDepth+1));
  }
  //distribute triangles among children
  for(unsigned int i = 0 ; i < curNode->tris.size(); i++){
    Triangle curTri = mesh->triangles[curNode->tris[i]];
    std::vector<Vec3> curTriPoints = {mesh->vertices[curTri.v0], mesh->vertices[curTri.v1], mesh->vertices[curTri.v2]};
    for(const auto& curOctant: curNode->children){
      if(curOctant->boundingBox.intersect_triangle(curTriPoints)){
        curOctant->tris.push_back(curNode->tris[i]);
      }
    }
  }
  for(auto& curOctant: curNode->children){
    build_recursive(curDepth + 1, curOctant, mesh);
  }
  /*
  if(curDepth < (maxDepth - 1)){
    curNode->tris.clear();
  }*/
}
std::vector<AABB> Octree::generate_octants(const AABB &box) {
  std::vector<AABB> octants;
  Vec3 center((box.maxVec.x + box.minVec.x)/2,(box.maxVec.y + box.minVec.y)/2,(box.maxVec.z + box.minVec.z)/2);
  octants.push_back(AABB(Vec3(box.minVec.x,box.minVec.y,box.minVec.z),Vec3(center.x,center.y,center.z)));
  octants.push_back(AABB(Vec3(center.x,box.minVec.y,box.minVec.z),Vec3(box.maxVec.x,center.y,center.z)));
  octants.push_back(AABB(Vec3(box.minVec.x,box.minVec.y,center.z),Vec3(center.x,center.y,box.maxVec.z)));
  octants.push_back(AABB(Vec3(center.x,box.minVec.y,center.z),Vec3(box.maxVec.x,center.y,box.maxVec.z)));
  octants.push_back(AABB(Vec3(box.minVec.x,center.y,box.minVec.z),Vec3(center.x,box.maxVec.y,center.z)));
  octants.push_back(AABB(Vec3(center.x,center.y,box.minVec.z),Vec3(box.maxVec.x,box.maxVec.y,center.z)));
  octants.push_back(AABB(Vec3(box.minVec.x,center.y,center.z),Vec3(center.x,box.maxVec.y,box.maxVec.z)));
  octants.push_back(AABB(Vec3(center.x,center.y,center.z),Vec3(box.maxVec.x,box.maxVec.y,box.maxVec.z)));
  return octants;
}

unsigned int Octree::count(std::shared_ptr<OctreeNode> curNode) {
  unsigned int cnt = 0;
  if(curNode->depth < maxDepth){
    for(auto& childNode : curNode->children){
      cnt += count(childNode);
    }
    return cnt;
  } else {
    cnt += curNode->tris.size();
    return cnt;
  }
}

void Octree::print_children() {
  std::cout << "Bounding box root: min " << root->boundingBox.minVec.to_string() << " max " << root->boundingBox.maxVec.to_string() << std::endl;
  for(int i = 0 ; i < 8; i++){
    std::cout << "Bounding box : min " << root->children[i]->boundingBox.minVec.to_string() << " max " << root->children[i]->boundingBox.maxVec.to_string() << std::endl;
  }
}