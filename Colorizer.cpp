//
// Created by Geno on 29-Aug-17.
//

#include "Colorizer.h"
#include <cmath>
#include <limits>
#include <iostream>

Color Colorizer::get_color(const SceneObject& obj,const Vec3& hitPoint,const Vec3& originPoint, unsigned int depth) {
  Color acumColor(0.0,0.0,0.0);
  if(depth <= renderParams.maxDepth){
    acumColor += get_indirect_color(obj);
    acumColor += get_direct_color(obj, hitPoint, originPoint);
    acumColor += get_reflected_color(obj, hitPoint,originPoint, depth);
    acumColor += get_refracted_color(obj, hitPoint,originPoint, depth);
  }
  return acumColor;
}

Color Colorizer::get_indirect_color(const SceneObject &obj) {
  if(sceneParams.sceneAmbientLight != nullptr){
    return sceneParams.sceneAmbientLight->color * obj.ambientColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_direct_color(const SceneObject &obj, const Vec3 &hitPoint, const Vec3& originPoint) {
  if(obj.brdfMats.size()){
    Color acumColor(0.0,0.0,0.0);
    for(auto const& curMat : obj.brdfMats){
      for(auto const& light: sceneParams.sceneLights){
        if(!in_shadow(hitPoint,*light)){
          acumColor += light->cast_on(*curMat, originPoint, obj.sphere, hitPoint);
        }
      }
    }
    return acumColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_reflected_color(const SceneObject &obj, const Vec3 &hitPoint,const Vec3& originPoint, unsigned int depth) {
  if(obj.reflectiveMats.size() > 0){
    Color acumColor(0.0,0.0,0.0);
    Vec3 normal = (hitPoint - obj.sphere.center).normalize();
    Vec3 eyeDir = (hitPoint - originPoint).normalize();
    Vec3 reflectDir = (eyeDir - (normal * ((eyeDir * 2).dot(normal)))).normalize();
    Ray reflectRay(hitPoint + reflectDir * eps, reflectDir);
    for(auto const& curMat : obj.reflectiveMats){
      Vec3 hitPos;
      std::shared_ptr<const SceneObject> closestObj;
      if(get_closest_object(reflectRay,hitPos,closestObj)){
        acumColor += curMat->baseColor * get_color(*closestObj,hitPos, hitPoint,depth + 1);
      }
    }
    return acumColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_refracted_color(const SceneObject &obj, const Vec3 &hitPoint,const Vec3& originPoint, unsigned int depth) {
  //This needs some refactor
  if(obj.dielectricMats.size() > 0){
    Vec3 entryNormal = (hitPoint - obj.sphere.center).normalize();
    Vec3 eyeDir = (hitPoint - originPoint).normalize();
    Vec3 reflectDir = (eyeDir - (entryNormal * ((eyeDir * 2).dot(entryNormal)))).normalize();
    Ray reflectRay(hitPoint + reflectDir * eps, reflectDir);
    Color reflectedColor;
    Color attenuationCoef;
    Vec3 hitPos;
    Ray refractRay;
    std::shared_ptr<const DielectricMaterial> curMat = obj.dielectricMats[0];
    std::shared_ptr<const SceneObject> closestObj;
    if(get_closest_object(reflectRay,hitPos,closestObj)){
      reflectedColor = get_color(*closestObj,hitPos, hitPoint,depth + 1);
    }
    //Reflection ends here
    double entryAngle;
    double fresnelCoef;
    if(eyeDir.dot(entryNormal) < 0) { //Entry
      refract(eyeDir,entryNormal,hitPoint,sceneParams.refractionIdx,curMat->refractionIdx,refractRay);
      entryAngle = entryNormal.dot(-eyeDir);
      fresnelCoef = fresnel_coef(curMat->refractionIdx,sceneParams.refractionIdx,entryAngle);
      attenuationCoef = Color(1.0,1.0,1.0);
    } else { //Exit
      double distance = (hitPoint - originPoint).magnitude();
      attenuationCoef = Color(std::exp(-curMat->attenuation.r()*distance),
                              std::exp(-curMat->attenuation.g()*distance),
                              std::exp(-curMat->attenuation.b()*distance));
      //Check TIR
      if(refract(eyeDir,-entryNormal,hitPoint,curMat->refractionIdx,sceneParams.refractionIdx,refractRay)){
        //No TIR
        entryAngle = -eyeDir.dot(-entryNormal);
        fresnelCoef = fresnel_coef(sceneParams.refractionIdx, curMat->refractionIdx,entryAngle);
      } else {
        //TIR return just reflected part
        return attenuationCoef * reflectedColor;
      }
    }
    Color refractedColor;
    Vec3 outPos;
    if(get_closest_object(refractRay,outPos,closestObj)){
      refractedColor = get_color(*closestObj,outPos,hitPoint,depth + 1);
    }
    return curMat->baseColor * attenuationCoef *((reflectedColor * fresnelCoef) + (refractedColor * (1.0 - fresnelCoef)));

  }
  return Color(0.0,0.0,0.0);
}

bool Colorizer::in_shadow(const Vec3 &hitPoint, const Light &light) {
  bool result = false;
  for(auto const& curObj : sceneParams.sceneObjs){
    Vec3 rayOutput;
    result |= light.cast_shadow_ray(hitPoint,curObj->sphere, eps, rayOutput);
  }
  return result;
}

bool Colorizer::get_closest_object(const Ray &hitRay, Vec3 &outPos, std::shared_ptr<const SceneObject>& outObj) {
  std::shared_ptr<SceneObject> closestCandidate = nullptr;
  double minDistance = std::numeric_limits<double>::max();
  bool hit = false;
  for (const auto &curObj : sceneParams.sceneObjs) {
    Vec3 out;
    if (bool curHit = hitRay.intersect_sphere(curObj->sphere, out)) {
      if ((out - hitRay.origin).magnitude() < minDistance) {
        hit |= curHit;
        minDistance = (out - hitRay.origin).magnitude();
        closestCandidate = curObj;
        outPos = out;
      }
    }
  }
  outObj = closestCandidate;
  return hit;
}
//Assumes normalized vectors
double Colorizer::total_internal_reflection_coef(const Vec3 &normal, const Vec3 &eyeDir, double rIdxIn,
                                                 double rIdxOut) {
  return 1.0 - (((rIdxOut*rIdxOut)/(rIdxIn*rIdxIn)) * ((normal.cross(eyeDir)).dot(normal.cross(eyeDir))));
}

Vec3 Colorizer::get_refraction_deviation(const Vec3 &normal, const Vec3 &eyeDir, double rIdxIn, double rIdxOut) {
  return ((normal.cross(-normal.cross(eyeDir))) * (rIdxOut/rIdxIn));
}

double Colorizer::fresnel_coef(double rIdxIn, double rIdxOut, double angleCosine) {
  double R_0 = std::pow((rIdxIn - rIdxOut)/(rIdxIn + rIdxOut),2);
  return R_0 + (1-R_0)*std::pow(1-angleCosine,5);
}

bool Colorizer::refract(const Vec3& entryDir, const Vec3& normal, const Vec3& hitPoint, double entryIdx, double exitIdx, Ray& out){
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