//
// Created by Geno on 25-Aug-17.
//

#include "Lights.h"
#include "Materials.h"
Color PointLight::cast_on(const BRDFMaterial& m, Camera& cam, Sphere &sphere, Vec3& rayHit) const{
  return m.get_color_from(*this,cam,sphere, rayHit);
}

Color DirectionalLight::cast_on(const BRDFMaterial &m, Camera &cam, Sphere &sphere, Vec3 &rayHit) const {
  return m.get_color_from(*this,cam,sphere,rayHit);
}

Color SpotLight::cast_on(const BRDFMaterial &m, Camera &cam, Sphere &sphere, Vec3 &rayHit) const {
  return m.get_color_from(*this,cam,sphere,rayHit);
}

//This is because these cast functions are for direct lighting, ambient lighting is not direct.
Color AmbientLight::cast_on(const BRDFMaterial &m, Camera &cam, Sphere &sphere, Vec3 &rayHit) const {
  return Color(0.0,0.0,0.0);
}