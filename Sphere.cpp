//
// Created by Geno on 31-Aug-17.
//

#include "Sphere.h"

bool Sphere::is_inside(const Vec3 &point) const {
  return (point-center).magnitude() <= radius;
}