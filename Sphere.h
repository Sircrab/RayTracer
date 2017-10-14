//
// Created by Geno on 12-Aug-17.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H
#include "Vec3.h"
struct Sphere{
    Vec3 center;
    double radius;
    Sphere(Vec3 center, double radius) : center(center), radius(radius){};
    Sphere() : center(Vec3(0,0,0)){};
    bool is_inside(const Vec3& point) const;
};

#endif //RAYTRACER_SPHERE_H
