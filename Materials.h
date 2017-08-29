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

protected:
    Material(Color baseColor): baseColor(baseColor){};
};

class BRDFMaterial : public Material{
public:
    bool isAmbient;
    //THESE ONLY HANDLE DIRECT LIGHTING ( NOT AMBIENT)
    virtual Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const Sphere &sphere,
                                 const Vec3 &rayHit) const=0;
    virtual Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const Sphere &sphere,
                                 const Vec3 &rayHit) const=0;
    virtual Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const Sphere &sphere,
                                 const Vec3 &rayHit) const=0;
protected:
    BRDFMaterial(Color baseColor, bool isAmbient) : Material(baseColor), isAmbient(isAmbient) {};
};

class LambertMaterial : public BRDFMaterial{
public:
    LambertMaterial(Color baseColor, bool isAmbient = false): BRDFMaterial(baseColor, isAmbient) {};
    Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const Sphere &sphere, const Vec3 &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const Sphere &sphere,
                         const Vec3 &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const Sphere &sphere, const Vec3 &rayHit) const override;
};

class BlinnPhongMaterial : public BRDFMaterial{
public:
    double shininess;
    BlinnPhongMaterial(Color baseColor, double shininess, bool isAmbient = false):
            BRDFMaterial(baseColor, isAmbient), shininess(shininess){};
    Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const Sphere &sphere, const Vec3 &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const Sphere &sphere,
                         const Vec3 &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const Sphere &sphere, const Vec3 &rayHit) const override;
};

class ReflectiveMaterial : public Material {
public:
    ReflectiveMaterial(Color baseColor) : Material(baseColor) {};
};

class DielectricMaterial : public Material {
public:
    Color attenuation;
    double refractionIdx;
    DielectricMaterial(Color baseColor, Color attenuation, double refractionIdx) :
            Material(baseColor), attenuation(attenuation), refractionIdx(refractionIdx) {}
};
#endif //RAYTRACER_MATERIAL_H
