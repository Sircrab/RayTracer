//
// Created by Geno on 25-Aug-17.
//
#include "Materials.h"
#include <cmath>
#include <iostream>

Color LambertMaterial::get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const Sphere &sphere,
                                      const Vec3 &rayHit) const {
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 lightVec = (pointLight.position - rayHit).normalize();
  return pointLight.color * baseColor * std::max(0.0, normal.dot(lightVec));
}
Color LambertMaterial::get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos,
                                      const Sphere &sphere, const Vec3 &rayHit) const {
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 lightVec = -directionalLight.direction.normalize();
  return directionalLight.color * baseColor * std::max(0.0, normal.dot(lightVec));
}
Color LambertMaterial::get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const Sphere &sphere,
                                      const Vec3 &rayHit) const {
  Vec3 lightVec = (rayHit - spotLight.position).normalize();
  Vec3 normal = (rayHit - sphere.center).normalize();
  double hitAngle = std::acos(lightVec.dot(spotLight.direction.normalize())) * (180.0/M_PI);
  return hitAngle <= spotLight.angle/2.0 ?
         spotLight.color * baseColor * std::max(0.0, normal.dot(-lightVec)) :
         Color(0.0,0.0,0.0);
}


Color BlinnPhongMaterial::get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const Sphere &sphere,
                                         const Vec3 &rayHit) const {
  Vec3 camVec = (cameraPos - rayHit).normalize();
  Vec3 lightVec = (pointLight.position - rayHit).normalize();
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 hVec = (camVec + lightVec).normalize();
  return pointLight.color * baseColor * std::pow(std::max(0.0, normal.dot(hVec)), shininess);
}
Color BlinnPhongMaterial::get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos,
                                         const Sphere &sphere, const Vec3 &rayHit) const {
  Vec3 camVec = (cameraPos - rayHit).normalize();
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 hVec = (camVec - directionalLight.direction.normalize()).normalize();
  return directionalLight.color * baseColor * std::pow(std::max(0.0, normal.dot(hVec)),shininess);
}
Color BlinnPhongMaterial::get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const Sphere &sphere,
                                         const Vec3 &rayHit) const {
  Vec3 camVec = (cameraPos - rayHit).normalize();
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 lightVec = (rayHit - spotLight.position).normalize();
  Vec3 hVec = (camVec - lightVec).normalize();
  double hitAngle = std::acos(lightVec.dot(spotLight.direction.normalize())) * (180.0/M_PI);
  return hitAngle <= spotLight.angle/2.0 ? spotLight.color * baseColor * std::pow(std::max(0.0,normal.dot(hVec)),shininess) :
         Color(0.0,0.0,0.0);
}


