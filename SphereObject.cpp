//
// Created by Geno on 17-Sep-17.
//
#include "SphereObject.h"
#include "Utils.h"
#include <cmath>
Vec3 SphereObject::get_normal(const Vec3 &pos) const {
  return (pos - sphere.center).normalize();
}

Vec2 SphereObject::get_uv(const Vec3 &pos) const {
  double theta = std::acos((pos.y - sphere.center.y)/sphere.radius);
  double phi = std::atan2(pos.z - sphere.center.z, pos.x - sphere.center.x);
  return Vec2(1-((M_PI + phi)/ (2*M_PI)),(M_PI - theta)/M_PI);
}

bool SphereObject::intersect_ray(const Ray &ray, RayCastHit &out) const {
  Vec3 sphereCenter = sphere.center;
  if(velocity.magnitude() > 0.0){
    sphereCenter += velocity* Utils::get_rand_time();
  }
  double det = pow(ray.direction.dot(ray.origin - sphereCenter),2) -
               pow((ray.origin - sphereCenter).magnitude(),2) + pow(sphere.radius,2);
  //1st case: No intersection
  if(det + Ray::eps < 0) return false;
  double ft = -(ray.direction.dot(ray.origin-sphereCenter));
  //2nd case: Tangent intersection
  if(det >= -Ray::eps && det <= Ray::eps){
    double d = ft + sqrt(det);
    if(abs(d) - Ray::eps < 0) return false;
    out.hitPos = ray.origin + ray.direction * d;
    out.normal = (out.hitPos - sphereCenter).normalize();
    return true;
  }
    //3rd Case: Double intersection
  else{
    double d1 = ft + sqrt(det);
    double d2 = ft - sqrt(det);
    //Assume d1 as smaller, otherwise swap it.
    if(d2 < d1){
      double tmp = d1;
      d1 = d2;
      d2 = tmp;
    }
    if(d1 + Ray::eps < 0){
      if(d2 + Ray::eps < 0){
        return false;
      }
      out.hitPos = ray.origin + ray.direction * d2;
      out.normal = (out.hitPos - sphereCenter).normalize();
      return true;
    }
    out.hitPos = ray.origin + ray.direction * d1;
    out.normal = (out.hitPos - sphereCenter).normalize();
    out.uv = get_uv(out.hitPos);
    return true;
  }
}

