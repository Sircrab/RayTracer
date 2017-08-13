//
// Created by Geno on 13-Aug-17.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#include "Vec3.h"
class Camera{
public:
    double cam_fov;
    Vec3 cam_up;
    Vec3 cam_pos;
    Vec3 cam_target;
    unsigned int scr_width;
    unsigned int scr_height;
    Camera(double cam_fov, Vec3 cam_up, Vec3 cam_pos, Vec3 cam_target,unsigned int scr_width,unsigned int scr_height);
    double get_top();
    double get_left();
    double get_right();
    double get_bottom();
    Vec3 get_w();
    Vec3 get_u();
    Vec3 get_v();
private:
    double top, left, right, bottom;
    Vec3 w, u ,v;
};
#endif //RAYTRACER_CAMERA_H
