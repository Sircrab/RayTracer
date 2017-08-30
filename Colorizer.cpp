//
// Created by Geno on 29-Aug-17.
//

#include "Colorizer.h"
#include <cmath>
#include <limits>

Color Colorizer::get_color(const SceneObject& obj,const Vec3& hitPoint, unsigned int depth) {
  Color acumColor(0.0,0.0,0.0);
  acumColor += get_indirect_color(obj);
  acumColor += get_direct_color(obj, hitPoint);
  acumColor += get_reflected_color(obj, hitPoint, depth);
  acumColor += get_refracted_color(obj, hitPoint, depth);
  return acumColor;
}

Color Colorizer::get_indirect_color(const SceneObject &obj) {
  if(sceneParams.sceneAmbientLight != nullptr){
    return sceneParams.sceneAmbientLight->color * obj.ambientColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_direct_color(const SceneObject &obj, const Vec3 &hitPoint) {
  if(obj.brdfMats.size()){
    Color acumColor(0.0,0.0,0.0);
    for(auto const& curMat : obj.brdfMats){
      for(auto const& light: sceneParams.sceneLights){
        if(!in_shadow(hitPoint,*light)){
          acumColor += light->cast_on(*curMat, sceneParams.cam_pos, obj.sphere, hitPoint);
        }
      }
    }
    return acumColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_reflected_color(const SceneObject &obj, const Vec3 &hitPoint, unsigned int depth) {
  if(obj.reflectiveMats.size() > 0 && depth < renderParams.maxDepth){
    Color acumColor(0.0,0.0,0.0);
    Vec3 normal = (hitPoint - obj.sphere.center).normalize();
    Vec3 eyeDir = (hitPoint - sceneParams.cam_pos).normalize();
    Vec3 reflectDir = (eyeDir - normal * ((eyeDir * 2).dot(normal)));
    Ray reflectRay(hitPoint + reflectDir * eps, reflectDir);
    for(auto const& curMat : obj.reflectiveMats){
      Vec3 hitPos;
      std::shared_ptr<SceneObject> closestObj;
      if(get_closest_object(reflectRay,hitPos,closestObj)){
        acumColor += curMat->baseColor * get_color(*closestObj,hitPos,depth + 1);
      }
    }
    return acumColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_refracted_color(const SceneObject &obj, const Vec3 &hitPoint, unsigned int depth) {
  if(obj.dielectricMats.size()){
    Color acumColor(0.0,0.0,0.0);
    //Rest here
    return acumColor;
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

bool Colorizer::get_closest_object(const Ray &hitRay, Vec3 &outPos, std::shared_ptr<SceneObject>& outObj) {
  std::shared_ptr<SceneObject> closestCandidate = nullptr;
  double minDistance = std::numeric_limits<double>::max();
  bool hit = false;
  for (const auto &curObj : sceneParams.sceneObjs) {
    Vec3 out;
    if (hit |= hitRay.intersect_sphere(curObj->sphere, out)) {
      if ((curObj->sphere.center - hitRay.origin).magnitude() < minDistance) {
        minDistance = (curObj->sphere.center - hitRay.origin).magnitude();
        closestCandidate = curObj;
        outPos = out;
      }
    }
  }
  outObj = closestCandidate;
  return hit;
}