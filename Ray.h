//
// Created by Geno on 12-Aug-17.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H
#include "Vec3.h"
#include "Sphere.h"
class Ray {
public:
    Vec3 origin;
    Vec3 direction;
    constexpr static double eps = 1.0e-9;
    Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction.normalize()){};
    bool intersect_sphere(Sphere s, Vec3& out);
};
#endif //RAYTRACER_RAY_H
