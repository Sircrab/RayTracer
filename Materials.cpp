//
// Created by Geno on 25-Aug-17.
//
#include "Materials.h"
#include <cmath>

Color LambertMaterial::get_color_from(PointLight pointLight, Camera camera, Sphere sphere, Vec3 rayHit) const {
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 lightVec = (pointLight.position - rayHit).normalize();
  return pointLight.color * baseColor * std::max(0.0, normal.dot(lightVec));
}
Color LambertMaterial::get_color_from(DirectionalLight directionalLight, Camera camera, Sphere sphere, Vec3 rayHit) const {
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 lightVec = -directionalLight.direction;
  return directionalLight.color * baseColor * std::max(0.0, normal.dot(lightVec));
}
Color LambertMaterial::get_color_from(SpotLight spotLight, Camera camera, Sphere sphere, Vec3 rayHit) const {
  Vec3 lightVec = (rayHit - spotLight.position).normalize();
  Vec3 normal = (rayHit - sphere.center).normalize();
  double hitAngle = std::acos((-lightVec).dot(spotLight.direction)) * (180.0/M_PI);
  return hitAngle <= spotLight.angle/2.0 ?
         spotLight.color * baseColor * std::max(0.0, normal.dot(lightVec)) :
         Color(0.0,0.0,0.0);
}
Color LambertMaterial::get_color_from(AmbientLight ambientLight, Camera camera, Sphere sphere, Vec3 rayHit) const {
  return Color(0.0,0.0,0.0);
}

Color BlinnPhongMaterial::get_color_from(PointLight pointLight, Camera camera, Sphere sphere, Vec3 rayHit) const {
  Vec3 camVec = (camera.cam_pos - rayHit).normalize();
  Vec3 lightVec = (pointLight.position - rayHit).normalize();
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 hVec = (camVec + lightVec).normalize();
  return pointLight.color * baseColor * std::pow(std::max(0.0, normal.dot(hVec)), shininess);
}
Color BlinnPhongMaterial::get_color_from(DirectionalLight directionalLight, Camera camera, Sphere sphere, Vec3 rayHit) const {
  Vec3 camVec = (camera.cam_pos - rayHit).normalize();
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 hVec = (camVec - directionalLight.direction).normalize();
  return directionalLight.color * baseColor * std::pow(std::max(0.0, normal.dot(hVec)),shininess);
}
Color BlinnPhongMaterial::get_color_from(SpotLight spotLight, Camera camera, Sphere sphere, Vec3 rayHit) const {
  Vec3 camVec = (camera.cam_pos - rayHit).normalize();
  Vec3 normal = (rayHit - sphere.center).normalize();
  Vec3 lightVec = (rayHit - spotLight.position).normalize();
  Vec3 hVec = (camVec + lightVec).normalize();
  double hitAngle = std::acos((-lightVec).dot(spotLight.direction)) * (180.0/M_PI);
  return hitAngle <= spotLight.angle/2.0 ? spotLight.color * baseColor * std::pow(std::max(0.0,normal.dot(hVec)),shininess) :
         Color(0.0,0.0,0.0);
}
Color BlinnPhongMaterial::get_color_from(AmbientLight ambientLight, Camera camera, Sphere sphere, Vec3 rayHit) const {
  return Color(0.0,0.0,0.0);
}

