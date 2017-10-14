//
// Created by Geno on 20-Sep-17.
//
#include "Triangle.h"
#include "Mesh.h"
#include <iostream>
//Based on Moller-Trumbore algorithm.
bool Triangle::intersect_ray(const Ray &ray,std::shared_ptr<const Mesh> mesh, RayCastHit &out) const{

  Vec3 v0v1 = mesh->vertices[v1] - mesh->vertices[v0];
  Vec3 v0v2 = mesh->vertices[v2] - mesh->vertices[v0];
  Vec3 pVec = ray.direction.cross(v0v2);
  double det = v0v1.dot(pVec);
  //No backface culling
  if(det > -Ray::eps && det < -Ray::eps) return false;
  double invDet = 1.0 / det;
  Vec3 tVec = ray.origin - mesh->vertices[v0];
  double u = tVec.dot(pVec) * invDet; // u parametric coordinate
  if (u < 0 || u > 1) return false; //outside of triangle
  Vec3 qVec = tVec.cross(v0v1);
  double v = ray.direction.dot(qVec) * invDet;
  if (v < 0 || u + v > 1) return false; //outside of triangle

  double t = v0v2.dot(qVec) * invDet;
  if(t < 0) return false;
  out.hitPos = ray.origin + ray.direction * t;
  out.normal = (mesh->normals[n1] * u + mesh->normals[n2] * v + mesh->normals[n0] * (1-u-v)).normalize();
  if(mesh->uvs.size() > 0){
    out.uv = mesh->uvs[uv1] * u + mesh->uvs[uv2] * v + mesh->uvs[uv0] * (1-u-v);
  } else {
    out.uv = Vec2(0, 0);
  }
  return true;
}
