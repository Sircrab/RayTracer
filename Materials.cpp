//
// Created by Geno on 25-Aug-17.
//
#include "Materials.h"
#include "RayCastHit.h"

Color ColorLambertMaterial::get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const {
  Vec3 lightVec = (pointLight.position - rayHit.hitPos).normalize();
  return pointLight.color * baseColor * std::max(0.0, rayHit.normal.dot(lightVec));
}
Color ColorLambertMaterial::get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos,
                                      const RayCastHit &rayHit) const {
  Vec3 lightVec = -directionalLight.direction.normalize();
  return directionalLight.color * baseColor * std::max(0.0, rayHit.normal.dot(lightVec));
}
Color ColorLambertMaterial::get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const {
  Vec3 lightVec = (rayHit.hitPos - spotLight.position).normalize();
  double hitAngle = std::acos(lightVec.dot(spotLight.direction.normalize())) * (180.0/M_PI);
  return hitAngle <= spotLight.angle/2.0 ?
         spotLight.color * baseColor * std::max(0.0, rayHit.normal.dot(-lightVec)) :
         Color(0.0,0.0,0.0);
}

Color ColorLambertMaterial::get_color_from(const AmbientLight &ambientLight, const Vec3 &cameraPos,
                                           const RayCastHit &rayHit) const {
  if(isAmbient){
    return ambientLight.color * baseColor;
  }
  return Color(0.0, 0.0, 0.0);
}


Color ColorBlinnPhongMaterial::get_color_from(const PointLight &pointLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const {
  Vec3 camVec = (cameraPos - rayHit.hitPos).normalize();
  Vec3 lightVec = (pointLight.position - rayHit.hitPos).normalize();
  Vec3 hVec = (camVec + lightVec).normalize();
  return pointLight.color * baseColor * std::pow(std::max(0.0, rayHit.normal.dot(hVec)), shininess);
}
Color ColorBlinnPhongMaterial::get_color_from(const DirectionalLight &directionalLight, const Vec3 &cameraPos,
                                         const RayCastHit &rayHit) const {
  Vec3 camVec = (cameraPos - rayHit.hitPos).normalize();
  Vec3 hVec = (camVec - directionalLight.direction.normalize()).normalize();
  return directionalLight.color * baseColor * std::pow(std::max(0.0, rayHit.normal.dot(hVec)),shininess);
}
Color ColorBlinnPhongMaterial::get_color_from(const SpotLight &spotLight, const Vec3 &cameraPos, const RayCastHit &rayHit) const {
  Vec3 camVec = (cameraPos - rayHit.hitPos).normalize();
  Vec3 lightVec = (rayHit.hitPos - spotLight.position).normalize();
  Vec3 hVec = (camVec - lightVec).normalize();
  double hitAngle = std::acos(lightVec.dot(spotLight.direction.normalize())) * (180.0/M_PI);
  return hitAngle <= spotLight.angle/2.0 ? spotLight.color * baseColor * std::pow(std::max(0.0,rayHit.normal.dot(hVec)),shininess) :
         Color(0.0,0.0,0.0);
}

Color ColorBlinnPhongMaterial::get_color_from(const AmbientLight &ambientLight, const Vec3 &cameraPos,
                                              const RayCastHit &rayHit) const {
  if(isAmbient){
    return ambientLight.color * baseColor;
  }
  return Color(0.0, 0.0, 0.0);
}


