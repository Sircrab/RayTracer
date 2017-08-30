//
// Created by Geno on 25-Aug-17.
//

#include "Lights.h"
#include "Materials.h"
#include "Ray.h"
Color PointLight::cast_on(const BRDFMaterial &m, Vec3 &camPos, const Sphere &sphere, const Vec3 &rayHit) const{
  return m.get_color_from(*this,camPos,sphere, rayHit);
}

bool PointLight::cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const {
  Vec3 lightDirection = (position - hitPoint).normalize();
  Ray shadowRay(hitPoint + lightDirection * shadowBias, lightDirection);
  return shadowRay.intersect_sphere(sphere,out);
}

Color DirectionalLight::cast_on(const BRDFMaterial &m, Vec3 &camPos, const Sphere &sphere, const Vec3 &rayHit) const {
  return m.get_color_from(*this,camPos,sphere,rayHit);
}

bool DirectionalLight::cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const {
  Vec3 lightDirection = -direction.normalize();
  Ray shadowRay(hitPoint + lightDirection*shadowBias, lightDirection);
  return shadowRay.intersect_sphere(sphere,out);
}

Color SpotLight::cast_on(const BRDFMaterial &m, Vec3 &camPos, const Sphere &sphere, const Vec3 &rayHit) const {
  return m.get_color_from(*this,camPos,sphere,rayHit);
}

bool SpotLight::cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const {
  Vec3 lightDirection = (position - hitPoint).normalize();
  Ray shadowRay(hitPoint + lightDirection * shadowBias, lightDirection);
  return shadowRay.intersect_sphere(sphere,out);
}

//This is because these cast functions are for direct lighting, ambient lighting is not direct.
Color AmbientLight::cast_on(const BRDFMaterial &m, Vec3 &camPos, const Sphere &sphere, const Vec3 &rayHit) const {
  return Color(0.0,0.0,0.0);
}
//Ambient light is never affected by shadows.
bool AmbientLight::cast_shadow_ray(const Vec3 &hitPoint, const Sphere &sphere, double shadowBias, Vec3 &out) const {
  return false;
}