//
// Created by Geno on 12-Aug-17.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H
#include "Vec3.h"
#include "Sphere.h"


//Forward declaration
class SceneObject;
class RayCastHit;
class Ray {
public:
    Vec3 origin;
    Vec3 direction;
    constexpr static double eps = 1.0e-9;
    Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction.normalize()){};
    Ray() : origin(Vec3()), direction(Vec3()){};
    bool intersect_object(const SceneObject& s, RayCastHit& out) const;
};
#endif //RAYTRACER_RAY_H
