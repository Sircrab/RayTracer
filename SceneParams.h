//
// Created by sircrab on 8/10/17.
//

#ifndef RAYTRACER_SCENEPARAMS_H
#define RAYTRACER_SCENEPARAMS_H
#include <vector>
#include <memory>
#include "Vec3.h"
#include "SceneObject.h"
#include "Lights.h"
#include "Camera.h"
class SceneParams{
public:
    std::vector<std::shared_ptr<SceneObject> > sceneObjs;
    std::vector<std::shared_ptr<const Light> > sceneLights;
    std::shared_ptr<const AmbientLight> sceneAmbientLight = nullptr;
    Color bgColor;
    Vec3 camPos;
    Vec3 camUp;
    Vec3 camTarget;
    double camFov;
    double refractionIdx = 1;
    std::shared_ptr<Camera> cam;
    SceneParams();
    void add_object(std::shared_ptr<SceneObject> object);
    void add_light(std::shared_ptr<const Light> light);
};
#endif //RAYTRACER_SCENEPARAMS_H
