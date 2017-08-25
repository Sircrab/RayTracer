//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H
#include "Lights.h"
#include "Color.h"
class Material{
public:
    Color baseColor;
    bool isAmbient;
    virtual Color get_color_from(PointLight pointLight) const=0;
    virtual Color get_color_from(DirectionalLight directionalLight) const=0;
    virtual Color get_color_from(SpotLight spotLight) const=0;
    virtual Color get_color_from(AmbientLight ambientLight) const=0;
protected:
    Material(Color baseColor, bool isAmbient): baseColor(baseColor), isAmbient(isAmbient){};
};

class LambertMaterial : public Material{
public:
    LambertMaterial(Color baseColor, bool isAmbient = false): Material(baseColor, isAmbient) {};
    Color get_color_from(PointLight pointLight) const override;
    Color get_color_from(DirectionalLight directionalLight) const override;
    Color get_color_from(SpotLight spotLight) const override;
    Color get_color_from(AmbientLight ambientLight) const override;
};

class BlinnPhongMaterial : public Material{
public:
    double shininess;
    BlinnPhongMaterial(Color baseColor, double shininess, bool isAmbient = false):
            Material(baseColor, isAmbient), shininess(shininess){};
    Color get_color_from(PointLight pointLight) const override;
    Color get_color_from(DirectionalLight directionalLight) const override;
    Color get_color_from(SpotLight spotLight) const override;
    Color get_color_from(AmbientLight ambientLight) const override;
};
#endif //RAYTRACER_MATERIAL_H
