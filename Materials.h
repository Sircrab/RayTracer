//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H
#include <memory>
#include "Lights.h"
#include "Color.h"
#include "Camera.h"
#include "Sphere.h"
#include "Texture.h"
//Forward Declaration
class RayCastHit;
class TextureFilter;

class Material{};

class TextureMaterial: Material{
public:
  std::shared_ptr<Texture> texture;
protected:
  TextureMaterial(std::shared_ptr<Texture> texture): texture(texture){};
};

class ColorMaterial : Material{
public:
    bool isAmbient;
    Color baseColor;

protected:
    ColorMaterial(Color baseColor, bool isAmbient): baseColor(baseColor), isAmbient(isAmbient){};
};

class BRDFMaterial : Material{
public:
    virtual Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const=0;
    virtual Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos,
                                 const RayCastHit &rayHit) const=0;
    virtual Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const=0;
    virtual Color get_color_from(const AmbientLight& ambientLight, const Vec3& cameraPos, const RayCastHit &rayHit) const=0;

};

class ColorBRDFMaterial : public ColorMaterial, public BRDFMaterial{
protected:
  ColorBRDFMaterial(Color baseColor, bool isAmbient): ColorMaterial(baseColor, isAmbient){};
};

class TextureBRDFMaterial : public TextureMaterial, public BRDFMaterial{
public:
  std::shared_ptr<TextureFilter> filter;
protected:
  TextureBRDFMaterial(std::shared_ptr<Texture> texture, std::shared_ptr<TextureFilter> filter) :
    TextureMaterial(texture), filter(filter){};
};

class ColorLambertMaterial : public ColorBRDFMaterial{
public:
    ColorLambertMaterial(Color baseColor, bool isAmbient = false): ColorBRDFMaterial(baseColor, isAmbient) {};
    Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const AmbientLight& ambientLight, const Vec3& cameraPos, const RayCastHit &rayHit) const;
};

class ColorBlinnPhongMaterial : public ColorBRDFMaterial{
public:
    double shininess;
    ColorBlinnPhongMaterial(Color baseColor, double shininess, bool isAmbient = false):
            ColorBRDFMaterial(baseColor, isAmbient), shininess(shininess){};
    Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const AmbientLight& ambientLight, const Vec3& cameraPos, const RayCastHit &rayHit) const;
};

class ReflectiveMaterial : public ColorMaterial {
public:
    ReflectiveMaterial(Color baseColor) : ColorMaterial(baseColor, false) {};
};

class DielectricMaterial : public ColorMaterial {
public:
    Color attenuation;
    double refractionIdx;
    DielectricMaterial(Color baseColor, Color attenuation, double refractionIdx) :
            ColorMaterial(baseColor, false), attenuation(attenuation), refractionIdx(refractionIdx) {}
};
#endif //RAYTRACER_MATERIAL_H
