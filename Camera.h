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
    virtual double get_top() const = 0;
    virtual double get_left() const = 0;
    virtual double get_right() const = 0;
    virtual double get_bottom() const = 0;
    virtual Vec3 get_w() const = 0;
    virtual Vec3 get_u() const = 0;
    virtual Vec3 get_v() const = 0;
    virtual double get_near() const = 0;
    virtual Vec3 get_position() const = 0;
    virtual Vec3 get_orig_position() const = 0;
protected:
  Camera(double cam_fov, Vec3 cam_up, Vec3 cam_pos, Vec3 cam_target,
         unsigned int scr_width, unsigned int scr_height) :
    cam_fov(cam_fov), cam_up(cam_up), cam_pos(cam_pos) ,
    cam_target(cam_target), scr_width(scr_width), scr_height(scr_height){};
  double top, left, right, bottom;
  Vec3 w, u ,v;

};
#endif //RAYTRACER_CAMERA_H
