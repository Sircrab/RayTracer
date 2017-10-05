//
// Created by Geno on 04-Oct-17.
//

#ifndef RAYTRACER_OCTREENODE_H
#define RAYTRACER_OCTREENODE_H
#include "AABB.h"
#include <memory>

class OctreeNode {
  friend class Octree;
  friend class MeshObject;
public:
  OctreeNode(): boundingBox(AABB(Vec3(0,0,0),Vec3(0,0,0))){};
  OctreeNode(AABB boundingBox, unsigned int depth): boundingBox(boundingBox), depth(depth){};
private:
  AABB boundingBox;
  std::vector<std::shared_ptr<OctreeNode> > children;
  unsigned int depth;
  std::vector<unsigned int> tris;
};
#endif //RAYTRACER_OCTREENODE_H
