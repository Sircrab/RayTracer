//
// Created by sircrab on 8/10/17.
//
#include "SceneParams.h"

SceneParams::SceneParams() :
        bg_color(Vec3(0,0,0)), cam_fov(0), cam_pos(Vec3(0,0,0)),
        cam_up(Vec3(0,0,0)), cam_target(Vec3(0,0,0)) {}

void SceneParams::add_object(std::shared_ptr<SceneObject> sceneObject) {
    sceneObjs.push_back(sceneObject);
}

void SceneParams::add_light(std::shared_ptr<const Light> light){
    sceneLights.push_back(light);
}

