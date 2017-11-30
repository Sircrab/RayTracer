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
#include "BRDFParams.h"
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
    Color baseColor;

protected:
    ColorMaterial(Color baseColor): baseColor(baseColor){};
};

class BRDFMaterial : Material{
public:
    virtual Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const=0;
    virtual Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos,
                                 const RayCastHit &rayHit) const=0;
    virtual Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const=0;
    virtual Color get_color_from(const AmbientLight& ambientLight, const Vec3& cameraPos, const RayCastHit &rayHit) const=0;
    virtual Color get_color_from(const AreaLight& areaLight, const Vec3& cameraPos, const RayCastHit &rayHit) const =0;

};

class ColorBRDFMaterial : public ColorMaterial, public BRDFMaterial{
public:
  BRDFParams params;
protected:
  ColorBRDFMaterial(Color baseColor, bool isAmbient): ColorMaterial(baseColor), params(isAmbient){};
  ColorBRDFMaterial(Color baseColor, bool isAmbient, double shininess): ColorMaterial(baseColor), params(isAmbient, shininess){};
};

class TextureBRDFMaterial : public TextureMaterial, public BRDFMaterial{
public:
  std::shared_ptr<TextureFilter> filter;
  BRDFParams params;

protected:
  TextureBRDFMaterial(std::shared_ptr<Texture> texture, std::shared_ptr<TextureFilter> filter, bool isAmbient) :
    TextureMaterial(texture), filter(filter), params(isAmbient){};
  TextureBRDFMaterial(std::shared_ptr<Texture> texture, std::shared_ptr<TextureFilter> filter, bool isAmbient, double shininess):
    TextureMaterial(texture), filter(filter), params(isAmbient, shininess){};
};

class ColorLambertMaterial : public ColorBRDFMaterial{
public:
    ColorLambertMaterial(Color baseColor, bool isAmbient = false): ColorBRDFMaterial(baseColor, isAmbient) {};
    Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const AmbientLight& ambientLight, const Vec3& cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const AreaLight& areaLight, const Vec3& cameraPos, const RayCastHit &rayHit) const override;
};

class ColorBlinnPhongMaterial : public ColorBRDFMaterial{
public:
    ColorBlinnPhongMaterial(Color baseColor, double shininess, bool isAmbient = false):
            ColorBRDFMaterial(baseColor, isAmbient, shininess){};
    Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const AmbientLight& ambientLight, const Vec3& cameraPos, const RayCastHit &rayHit) const override;
    Color get_color_from(const AreaLight& areaLight, const Vec3& cameraPos, const RayCastHit &rayHit) const override;
};

class TextureLambertMaterial : public TextureBRDFMaterial{
public:
  TextureLambertMaterial(std::shared_ptr<Texture> texture, std::shared_ptr<TextureFilter> filter, bool isAmbient) :
    TextureBRDFMaterial(texture, filter,isAmbient){};
  Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
  Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
  Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
  Color get_color_from(const AmbientLight& ambientLight, const Vec3& cameraPos, const RayCastHit &rayHit) const override;
  Color get_color_from(const AreaLight& areaLight, const Vec3& cameraPos, const RayCastHit &rayHit) const override;
};

class TextureBlinnPhongMaterial : public TextureBRDFMaterial{
public:
  TextureBlinnPhongMaterial(std::shared_ptr<Texture> texture, std::shared_ptr<TextureFilter> filter, bool isAmbient, double shininess) :
    TextureBRDFMaterial(texture, filter, isAmbient, shininess){};
  Color get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
  Color get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
  Color get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const override;
  Color get_color_from(const AmbientLight& ambientLight, const Vec3& cameraPos, const RayCastHit &rayHit) const override;
  Color get_color_from(const AreaLight& areaLight, const Vec3& cameraPos, const RayCastHit &rayHit) const override;
};

class ReflectiveMaterial : public ColorMaterial {
public:
    double glossyFactor;
    ReflectiveMaterial(Color baseColor, double glossyFactor) : ColorMaterial(baseColor), glossyFactor(glossyFactor) {};

};

class DielectricMaterial : public ColorMaterial {
public:
    Color attenuation;
    double refractionIdx;
    DielectricMaterial(Color baseColor, Color attenuation, double refractionIdx) :
            ColorMaterial(baseColor), attenuation(attenuation), refractionIdx(refractionIdx) {}
};
#endif //RAYTRACER_MATERIAL_H
