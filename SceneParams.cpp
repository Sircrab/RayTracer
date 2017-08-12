//
// Created by sircrab on 8/10/17.
//
#include "SceneParams.h"

SceneParams::SceneParams() :
        bg_color(Vec3(0,0,0)), cam_fov(0), cam_pos(Vec3(0,0,0)),
        cam_up(Vec3(0,0,0)), cam_target(Vec3(0,0,0)){
    this->scene_objs = new std::vector<Sphere>();
}

SceneParams::~SceneParams() {
    delete this->scene_objs;
}

SceneParams::SceneParams(const SceneParams &other) :
        bg_color(other.bg_color), cam_fov(other.cam_fov), cam_pos(other.cam_pos),
        cam_up(other.cam_up), cam_target(other.cam_target){
    this->scene_objs = new std::vector<Sphere>(other.scene_objs->size());
    for(int i = 0; i < other.scene_objs->size(); i++){
        this->scene_objs[i].push_back((*other.scene_objs)[i]);
    }
}

SceneParams& SceneParams::operator=(const SceneParams &other) {
    this->bg_color = other.bg_color;
    this->cam_up = other.cam_up;
    this->cam_fov = other.cam_fov;
    this->cam_pos = other.cam_pos;
    this->cam_target = other.cam_target;
    delete scene_objs;
    this->scene_objs = new std::vector<Sphere>(other.scene_objs->size());
    for(int i = 0; i < other.scene_objs->size(); i++){
        this->scene_objs[i].push_back((*other.scene_objs)[i]);
    }
}

void SceneParams::add_sphere(Vec3 center, double radius) {
    this->scene_objs->push_back(Sphere(center,radius));
}
