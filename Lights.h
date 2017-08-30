//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H
#include "Color.h"
#include "Camera.h"
#include "Sphere.h"
class BRDFMaterial; //Forward declaration

class Light{
public:
    virtual Color cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Sphere &sphere, const Vec3 &rayHit) const =0;
    virtual bool cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const=0;
};

class PointLight : public Light{
public:
    Vec3 position;
    Color color;
    PointLight(Vec3 position, Color color): position(position), color(color){};
    Color cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Sphere &sphere, const Vec3 &rayHit) const override;
    bool cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const override;
};

class DirectionalLight : public Light{
public:
    Vec3 direction;
    Color color;
    DirectionalLight(Vec3 direction, Color color): direction(direction), color(color){};
    Color cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Sphere &sphere, const Vec3 &rayHit) const override;
    bool cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const override;
};

class SpotLight : public Light{
public:
    Vec3 position, direction;
    double angle;
    Color color;
    SpotLight(Vec3 position, Vec3 direction, double angle, Color color):
            position(position), direction(direction), angle(angle), color(color){};
    Color cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Sphere &sphere, const Vec3 &rayHit) const override;
    bool cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const override;
};

class AmbientLight : public Light{
public:
    Color color;
    AmbientLight(Color color): color(color){};
    Color cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Sphere &sphere, const Vec3 &rayHit) const override;
    bool cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const override;
};
#endif //RAYTRACER_LIGHT_H
