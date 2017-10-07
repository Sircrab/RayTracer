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
    Vec3 invDir;
    constexpr static double eps = 1.0e-9;
    Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction.normalize()){
      invDir = Vec3(1.0 / direction.x, 1.0 / direction.y, 1.0 / direction.z);
    };
    Ray() : origin(Vec3()), direction(Vec3()){};
    bool intersect_object(const SceneObject& s, RayCastHit& out) const;
};
#endif //RAYTRACER_RAY_H
