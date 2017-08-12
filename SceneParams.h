//
// Created by sircrab on 8/10/17.
//

#ifndef RAYTRACER_SCENEPARAMS_H
#define RAYTRACER_SCENEPARAMS_H
#include <vector>
#include <memory>
#include "Vec3.h"
#include "Sphere.h"
class SceneParams{
public:
    std::vector<Sphere>* scene_objs;
    Vec3 bg_color;
    Vec3 cam_pos;
    Vec3 cam_up;
    Vec3 cam_target;
    double cam_fov;
    SceneParams();
    SceneParams(const SceneParams& other);
    ~SceneParams();
    SceneParams& operator= (const SceneParams& other);
    void add_sphere(Vec3 center, double radius);
};
#endif //RAYTRACER_SCENEPARAMS_H
