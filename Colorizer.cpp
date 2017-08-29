//
// Created by Geno on 29-Aug-17.
//

#include "Colorizer.h"

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
        acumColor += light->cast_on(*curMat, sceneParams.cam_pos, obj.sphere, hitPoint);
      }
    }
    return acumColor;
  }
  return Color(0.0,0.0,0.0);
}

Color Colorizer::get_reflected_color(const SceneObject &obj, const Vec3 &hitPoint, unsigned int depth) {
  if(obj.reflectiveMats.size()){
    Color acumColor(0.0,0.0,0.0);
    //Rest here
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