//
// Created by Geno on 29-Aug-17.
//

#include "Colorizer.h"
#include <cmath>
#include <limits>
#include <iostream>

Color Colorizer::get_color(const SceneObject &obj, const RayCastHit &rayHit, const Vec3 &originPoint,
                           unsigned int depth) {
  Color acumColor(0.0,0.0,0.0);
  if(depth <= renderParams->maxDepth){
    acumColor += get_indirect_color(obj);
    acumColor += get_direct_color(obj, rayHit, originPoint);
    acumColor += get_reflected_color(obj, rayHit,originPoint, depth);
    acumColor += get_refracted_color(obj, rayHit,originPoint, depth);
  }
  return acumColor;
}

Color Colorizer::get_indirect_color(const SceneObject &obj) {
  if(sceneParams->sceneAmbientLight != nullptr){
    return sceneParams->sceneAmbientLight->color * obj.ambientColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_direct_color(const SceneObject &obj, const RayCastHit &rayHit, const Vec3 &originPoint) {
  if(obj.brdfMats.size()){
    Color acumColor(0.0,0.0,0.0);
    for(auto const& curMat : obj.brdfMats){
      for(auto const& light: sceneParams->sceneLights){
        if(!in_shadow(rayHit.hitPos,*light)) {
          acumColor += light->cast_on(*curMat, originPoint, rayHit.normal, rayHit.hitPos);
        }
      }
    }
    return acumColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_reflected_color(const SceneObject &obj, const RayCastHit &rayHit, const Vec3 &originPoint,
                                     unsigned int depth) {
  if(obj.reflectiveMat){
    Ray reflectRay = reflect(rayHit.hitPos, originPoint, rayHit.normal);
    RayCastHit reflectRayHit;
    std::shared_ptr<const SceneObject> closestObj;
    if(get_closest_object(reflectRay,reflectRayHit,closestObj)){
      return obj.reflectiveMat->baseColor * get_color(*closestObj,reflectRayHit, rayHit.hitPos, depth + 1);
    }
    return sceneParams->bgColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_refracted_color(const SceneObject &obj, const RayCastHit &rayHit, const Vec3 &originPoint,
                                     unsigned int depth) {
  //This needs some refactor
  if(obj.dielectricMat){
    Vec3 entryNormal = rayHit.normal;
    Vec3 eyeDir = (rayHit.hitPos - originPoint).normalize();
    Ray reflectRay = reflect(rayHit.hitPos, originPoint, entryNormal);
    Color reflectedColor;
    Color attenuationCoef;
    RayCastHit reflectRayHit;
    Ray refractRay;
    std::shared_ptr<const DielectricMaterial> curMat = obj.dielectricMat;
    std::shared_ptr<const SceneObject> closestObj;
    if(get_closest_object(reflectRay,reflectRayHit,closestObj)){
      reflectedColor = get_color(*closestObj,reflectRayHit, rayHit.hitPos,depth + 1);
    }
    //Reflection ends here
    double entryAngle;
    double fresnelCoef;
    if(eyeDir.dot(entryNormal) < 0) { //Entry
      refract(eyeDir,entryNormal,rayHit.hitPos,sceneParams->refractionIdx,curMat->refractionIdx,refractRay);
      entryAngle = entryNormal.dot(-eyeDir);
      fresnelCoef = fresnel_coef(curMat->refractionIdx,sceneParams->refractionIdx,entryAngle);
      attenuationCoef = Color(1.0,1.0,1.0);
    } else { //Exit
      double distance = (rayHit.hitPos - originPoint).magnitude();
      attenuationCoef = Color(std::exp(-curMat->attenuation.r()*distance),
                              std::exp(-curMat->attenuation.g()*distance),
                              std::exp(-curMat->attenuation.b()*distance));
      //Check TIR
      if(refract(eyeDir,-entryNormal,rayHit.hitPos,curMat->refractionIdx,sceneParams->refractionIdx,refractRay)){
        //No TIR
        entryAngle = -eyeDir.dot(-entryNormal);
        fresnelCoef = fresnel_coef(sceneParams->refractionIdx, curMat->refractionIdx,entryAngle);
      } else {
        //TIR return just reflected part
        return curMat->baseColor * attenuationCoef * reflectedColor;
      }
    }
    Color refractedColor;
    RayCastHit refractRayHit;
    if(get_closest_object(refractRay,refractRayHit,closestObj)){
      refractedColor = get_color(*closestObj,refractRayHit,rayHit.hitPos,depth + 1);
    } else {
      //Border case for TIR on entry
      return curMat->baseColor * attenuationCoef * reflectedColor;
    }
    return curMat->baseColor * attenuationCoef *((reflectedColor * fresnelCoef) + (refractedColor * (1.0 - fresnelCoef)));
  }
  return Color(0.0,0.0,0.0);
}

bool Colorizer::in_shadow(const Vec3 &hitPoint, const Light &light) {
  bool result = false;
  for(auto const& curObj : sceneParams->sceneObjs){
    RayCastHit rayOutput;
    result |= light.cast_shadow_ray(hitPoint,*curObj, eps, rayOutput);
  }
  return result;
}

bool Colorizer::get_closest_object(const Ray &hitRay, RayCastHit &rayHit, std::shared_ptr<const SceneObject> &outObj) {
  std::shared_ptr<SceneObject> closestCandidate = nullptr;
  double minDistance = std::numeric_limits<double>::max();
  bool hit = false;
  for (const auto &curObj : sceneParams->sceneObjs) {
    RayCastHit out;
    if (bool curHit = curObj->intersect_ray(hitRay,out)) {
      if ((out.hitPos - hitRay.origin).magnitude() < minDistance) {
        hit |= curHit;
        minDistance = (out.hitPos - hitRay.origin).magnitude();
        closestCandidate = curObj;
        rayHit = out;
      }
    }
  }
  outObj = closestCandidate;
  return hit;
}
//Assumes normalized vectors
double Colorizer::total_internal_reflection_coef(const Vec3 &normal, const Vec3 &eyeDir, double rIdxIn,
                                                 double rIdxOut) const{
  return 1.0 - (((rIdxOut*rIdxOut)/(rIdxIn*rIdxIn)) * ((normal.cross(eyeDir)).dot(normal.cross(eyeDir))));
}

Vec3 Colorizer::get_refraction_deviation(const Vec3 &normal, const Vec3 &eyeDir, double rIdxIn, double rIdxOut) const{
  return ((normal.cross(-normal.cross(eyeDir))) * (rIdxOut/rIdxIn));
}

double Colorizer::fresnel_coef(double rIdxIn, double rIdxOut, double angleCosine) const{
  double R_0 = std::pow((rIdxIn - rIdxOut)/(rIdxIn + rIdxOut),2);
  return R_0 + (1-R_0)*std::pow(1-angleCosine,5);
}

bool Colorizer::refract(const Vec3& entryDir, const Vec3& normal, const Vec3& hitPoint, double entryIdx, double exitIdx, Ray& out) const{
  double TIRIdx = total_internal_reflection_coef(normal,entryDir,exitIdx,entryIdx);
  if(TIRIdx < 0){
    return false;
  } else {
    Vec3 refractDir = (get_refraction_deviation(normal, entryDir, exitIdx, entryIdx) -
                      normal * std::sqrt(TIRIdx)).normalize();
    out = Ray(hitPoint + refractDir * eps,refractDir);
    return true;
  }
}

Ray Colorizer::reflect(const Vec3 &hitPoint, const Vec3 &originPoint, const Vec3 &normal) const{
  Vec3 eyeDir = (hitPoint - originPoint).normalize();
  Vec3 reflectDir = (eyeDir - (normal * ((eyeDir * 2).dot(normal)))).normalize();
  return Ray(hitPoint + reflectDir * eps, reflectDir);
}