//
// Created by sircrab on 8/10/17.
//
#include "SceneParams.h"

SceneParams::SceneParams() :
        bgColor(Color(0,0,0)), camFov(0), camPos(Vec3(0,0,0)),
        camUp(Vec3(0,0,0)), camTarget(Vec3(0,0,0)) {}

void SceneParams::add_object(std::shared_ptr<SceneObject> sceneObject) {
    sceneObjs.push_back(sceneObject);
}

void SceneParams::add_light(std::shared_ptr<const Light> light){
    sceneLights.push_back(light);
}

