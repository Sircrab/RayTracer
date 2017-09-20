//
// Created by Geno on 25-Aug-17.
//

#include "Lights.h"
#include "Materials.h"
#include "Ray.h"
#include "SceneObject.h"
#include <limits>
Color PointLight::cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Vec3 &normal, const Vec3 &rayHit) const{
  return m.get_color_from(*this,originPos,normal, rayHit);
}

bool PointLight::cast_shadow_ray(const Vec3 &hitPoint, const SceneObject &obj, double shadowBias, RayCastHit &out) const {
  Vec3 lightDirection = (position - hitPoint).normalize();
  Ray shadowRay(hitPoint + lightDirection * shadowBias, lightDirection);
  double distance = (position - hitPoint).magnitude();
  return obj.intersect_ray(shadowRay,out) && (out.hitPos-hitPoint).magnitude() < distance;
}

Color DirectionalLight::cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Vec3 &normal, const Vec3 &rayHit) const {
  return m.get_color_from(*this,originPos,normal,rayHit);
}

bool DirectionalLight::cast_shadow_ray(const Vec3 &hitPoint, const SceneObject &obj, double shadowBias, RayCastHit &out) const {
  Vec3 lightDirection = -direction.normalize();
  Ray shadowRay(hitPoint + lightDirection*shadowBias, lightDirection);
  double distance = std::numeric_limits<double>::max();
  return obj.intersect_ray(shadowRay,out)  && (out.hitPos-hitPoint).magnitude() < distance;
}

Color SpotLight::cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Vec3 &normal, const Vec3 &rayHit) const {
  return m.get_color_from(*this,originPos,normal,rayHit);
}

bool SpotLight::cast_shadow_ray(const Vec3 &hitPoint, const SceneObject &obj, double shadowBias, RayCastHit &out) const {
  Vec3 lightDirection = (position - hitPoint).normalize();
  Ray shadowRay(hitPoint + lightDirection * shadowBias, lightDirection);
  double distance = (position - hitPoint).magnitude();
  return obj.intersect_ray(shadowRay,out)  && (out.hitPos-hitPoint).magnitude() < distance;
}

//This is because these cast functions are for direct lighting, ambient lighting is not direct.
Color AmbientLight::cast_on(const BRDFMaterial &m, const Vec3 &originPos, const Vec3 &normal, const Vec3 &rayHit) const {
  return Color(0.0,0.0,0.0);
}
//Ambient light is never affected by shadows.
bool AmbientLight::cast_shadow_ray(const Vec3 &hitPoint, const SceneObject &obj, double shadowBias, RayCastHit &out) const {
  return false;
}