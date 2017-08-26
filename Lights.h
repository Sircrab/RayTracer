//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H
#include "Color.h"
class Light{

};

class PointLight : public Light{
public:
    Vec3 position;
    Color color;
    PointLight(Vec3 position, Color color): position(position), color(color){};
};

class DirectionalLight : public Light{
public:
    Vec3 direction;
    Color color;
    DirectionalLight(Vec3 direction, Color color): direction(direction), color(color){};
};

class SpotLight : public Light{
public:
    Vec3 position, direction;
    double angle;
    Color color;
    SpotLight(Vec3 position, Vec3 direction, double angle, Color color):
            position(position), direction(direction), angle(angle), color(color){};
};

class AmbientLight : public Light{
public:
    Color color;
    AmbientLight(Color color): color(color){};
};
#endif //RAYTRACER_LIGHT_H
