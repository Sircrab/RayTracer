//
// Created by Geno on 25-Aug-17.
//
#include "Parser.h"
#include "cxxopts/cxxopts.hpp"
#include "json/json.hpp"
#include "SphereObject.h"
#include <string>
#include <fstream>
#include <algorithm>

RenderParams Parser::parse_params(int argc, char **argv) {
  cxxopts::Options options("RayTracer","Simple raytracer");
  options.add_options()
          ("w,width","Render width",cxxopts::value<unsigned int>())
  ("h,height","Render height",cxxopts::value<unsigned int>())
  ("s,scene","Scene description file",cxxopts::value<std::string>())
          ("i,image","Image file output",cxxopts::value<std::string>())
          ("r,resources", "Scene objects Resources", cxxopts::value<std::string>())
          ("m, maxDepth", "Maximum ray depth", cxxopts::value<unsigned int>()->default_value("3"));
  options.parse(argc,argv);
  RenderParams r(options["w"].as<unsigned int>(),options["h"].as<unsigned int>(),
          options["i"].as<std::string>(),options["s"].as<std::string>(),
          options["r"].as<std::string>(),options["m"].as<unsigned int>());
  return r;
}

SceneMaterials Parser::parse_materials(RenderParams& renderParams) {
  SceneMaterials sceneMaterials;
  nlohmann::json j;
  std::ifstream file(renderParams.resources_file);
  file >> j;
  for(auto& elem : j["materials"]){
    Color color(elem["color"][0],elem["color"][1],elem["color"][2]);
    std::string name = elem["name"];
    if(elem["__type__"] == "brdf_material"){
      bool isAmbient = false;
      if(elem.count("use_for_ambient")){
        isAmbient = elem["use_for_ambient"];
      }
      if(elem["brdf"] == "lambert"){
        sceneMaterials.add_brdf_material(name, std::make_shared<const LambertMaterial>(color,isAmbient));
      } else if (elem["brdf"] == "blinnPhong"){
        double shininess = elem["brdfParams"]["shininess"];
        sceneMaterials.add_brdf_material(name, std::make_shared<const BlinnPhongMaterial>(color,shininess,isAmbient));
      }
    } else if(elem["__type__"] == "reflective_material"){
      sceneMaterials.add_reflective_material(name, std::make_shared<const ReflectiveMaterial>(color));
    } else if(elem["__type__"] == "dielectric_material"){
      Color attenuation(elem["attenuation"][0],elem["attenuation"][1],elem["attenuation"][2]);
      double refractionIdx = elem["refraction_index"];
      sceneMaterials.add_dielectric_material(name,std::make_shared<const DielectricMaterial>(color,attenuation,refractionIdx));
    }
  }
  return sceneMaterials;
}

SceneParams Parser::parse_scene(RenderParams& renderParams, SceneMaterials& sceneMaterials) {
  SceneParams p;
  nlohmann::json j;
  std::ifstream file(renderParams.json_file);
  file >> j;
  p.camFov = j["camera"]["fov"];
  p.camPos = Vec3(j["camera"]["position"][0],j["camera"]["position"][1],j["camera"]["position"][2]);
  p.camUp = Vec3(j["camera"]["up"][0],j["camera"]["up"][1],j["camera"]["up"][2]);
  p.camTarget = Vec3(j["camera"]["target"][0],j["camera"]["target"][1],j["camera"]["target"][2]);
  p.bgColor = Color(j["params"]["background_color"][0],j["params"]["background_color"][1],j["params"]["background_color"][2]);
  if(j["params"].count("refraction_index")){
    p.refractionIdx = j["params"]["refraction_index"];
  }
  for(auto& elem : j["objects"]){
    if(elem["__type__"] == "sphere"){
      auto curObj = std::make_shared<SphereObject>
              (Sphere(Vec3(elem["position"][0],elem["position"][1],elem["position"][2]), elem["radius"]));
      for(auto& mats : elem["materials"]){
        if(sceneMaterials.brdfMats.count(mats)){
          curObj->attach_brdf_material(sceneMaterials.brdfMats[mats]);
        } else if(sceneMaterials.reflectiveMats.count(mats)){
          curObj->set_reflective_material(sceneMaterials.reflectiveMats[mats]);
        } else if(sceneMaterials.dielectricMats.count(mats)){
          curObj->set_dielectric_material(sceneMaterials.dielectricMats[mats]);
        }
      }
      p.add_object(curObj);
    }
  }

  for(auto& elem : j["lights"]){
    if(elem["__type__"] == "point_light"){
      Vec3 pos(elem["position"][0],elem["position"][1],elem["position"][2]);
      Color color(elem["color"][0],elem["color"][1],elem["color"][2]);
      p.add_light(std::make_shared<const PointLight>(pos,color));
    } else if(elem["__type__"] == "directional_light") {
      Vec3 dir(elem["direction"][0],elem["direction"][1],elem["direction"][2]);
      Color color(elem["color"][0],elem["color"][1],elem["color"][2]);
      p.add_light(std::make_shared<const DirectionalLight>(dir,color));
    } else if(elem["__type__"] == "spot_light"){
      Vec3 pos(elem["position"][0],elem["position"][1],elem["position"][2]);
      Color color(elem["color"][0],elem["color"][1],elem["color"][2]);
      Vec3 dir(elem["direction"][0],elem["direction"][1],elem["direction"][2]);
      double angle = elem["angle"];
      p.add_light(std::make_shared<const SpotLight>(pos,dir,angle,color));
    } else if(elem["__type__"] == "ambient_light"){
      Color color(elem["color"][0],elem["color"][1],elem["color"][2]);
      std::shared_ptr<const AmbientLight> ambLight = std::make_shared<const AmbientLight>(color);
      p.add_light(ambLight);
      //First ambient light assumed for scene.
      if(p.sceneAmbientLight == nullptr){
        p.sceneAmbientLight = ambLight;
      }
    }
  }
  file.close();
  return p;
}
