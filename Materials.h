//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H
#include "Lights.h"
#include "Color.h"
#include "Camera.h"
#include "Sphere.h"
class Material{
public:
    Color baseColor;
    bool isAmbient;
    //THESE ONLY HANDLE DIRECT LIGHTING ( NOT AMBIENT)
    virtual Color get_color_from(const PointLight &pointLight, const Camera &camera, const Sphere &sphere,
                                 const Vec3 &rayHit) const=0;
    virtual Color get_color_from(const DirectionalLight &directionalLight, const Camera &camera, const Sphere &sphere,
                                 const Vec3 &rayHit) const=0;
    virtual Color get_color_from(const SpotLight &spotLight, const Camera &camera, const Sphere &sphere,
                                 const Vec3 &rayHit) const=0;
protected:
    Material(Color baseColor, bool isAmbient): baseColor(baseColor), isAmbient(isAmbient){};
};

class LambertMaterial : public Material{
public:
    LambertMaterial(Color baseColor, bool isAmbient = false): Material(baseColor, isAmbient) {};
    Color get_color_from(const PointLight &pointLight, const Camera &camera, const Sphere &sphere, const Vec3 &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Camera &camera, const Sphere &sphere,
                         const Vec3 &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Camera &camera, const Sphere &sphere, const Vec3 &rayHit) const override;
};

class BlinnPhongMaterial : public Material{
public:
    double shininess;
    BlinnPhongMaterial(Color baseColor, double shininess, bool isAmbient = false):
            Material(baseColor, isAmbient), shininess(shininess){};
    Color get_color_from(const PointLight &pointLight, const Camera &camera, const Sphere &sphere, const Vec3 &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Camera &camera, const Sphere &sphere,
                         const Vec3 &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Camera &camera, const Sphere &sphere, const Vec3 &rayHit) const override;
};
#endif //RAYTRACER_MATERIAL_H
