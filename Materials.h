//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H
#include "Lights.h"
#include "Color.h"
#include "Camera.h"
#include "Sphere.h"
class Material{};
class ColorMaterial : Material{
public:
    Color baseColor;

protected:
    ColorMaterial(Color baseColor): baseColor(baseColor){};
};

class ColorBRDFMaterial : public ColorMaterial{
public:
    bool isAmbient;
    //THESE ONLY HANDLE DIRECT LIGHTING ( NOT AMBIENT)
    virtual Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const Vec3 &normal,
                                 const Vec3 &rayHit) const=0;
    virtual Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const Vec3 &normal,
                                 const Vec3 &rayHit) const=0;
    virtual Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const Vec3 &normal,
                                 const Vec3 &rayHit) const=0;
protected:
    ColorBRDFMaterial(Color baseColor, bool isAmbient) : ColorMaterial(baseColor), isAmbient(isAmbient) {};
};

class LambertMaterial : public ColorBRDFMaterial{
public:
    LambertMaterial(Color baseColor, bool isAmbient = false): ColorBRDFMaterial(baseColor, isAmbient) {};
    Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const Vec3 &normal, const Vec3 &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const Vec3 &normal,
                         const Vec3 &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const Vec3 &normal, const Vec3 &rayHit) const override;
};

class BlinnPhongMaterial : public ColorBRDFMaterial{
public:
    double shininess;
    BlinnPhongMaterial(Color baseColor, double shininess, bool isAmbient = false):
            ColorBRDFMaterial(baseColor, isAmbient), shininess(shininess){};
    Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const Vec3 &normal, const Vec3 &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const Vec3 &normal,
                         const Vec3 &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const Vec3 &normal, const Vec3 &rayHit) const override;
};

class ReflectiveMaterial : public ColorMaterial {
public:
    ReflectiveMaterial(Color baseColor) : ColorMaterial(baseColor) {};
};

class DielectricMaterial : public ColorMaterial {
public:
    Color attenuation;
    double refractionIdx;
    DielectricMaterial(Color baseColor, Color attenuation, double refractionIdx) :
            ColorMaterial(baseColor), attenuation(attenuation), refractionIdx(refractionIdx) {}
};
#endif //RAYTRACER_MATERIAL_H
