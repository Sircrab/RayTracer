#include <iostream>
#include <fstream>
#include <vector>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "SceneParams.h"
#include "RenderParams.h"
#include "Camera.h"
#include "lodepng/lodepng.h"
#include "cxxopts/cxxopts.hpp"
#include "json/json.hpp"

struct Pixel{
  unsigned char R;
  unsigned char G;
  unsigned char B;
  unsigned char A;
};

SceneParams parse_scene(RenderParams renderParams){
  SceneParams p;
  nlohmann::json j;
  std::ifstream file(renderParams.json_file);
  file >> j;
  p.cam_fov = j["camera"]["fov"];
  p.cam_pos = Vec3(j["camera"]["position"][0],j["camera"]["position"][1],j["camera"]["position"][2]);
  p.cam_up = Vec3(j["camera"]["up"][0],j["camera"]["up"][1],j["camera"]["up"][2]);
  p.cam_target = Vec3(j["camera"]["target"][0],j["camera"]["target"][1],j["camera"]["target"][2]);
  p.bg_color = Vec3(j["params"]["background_color"][0],j["params"]["background_color"][1],j["params"]["background_color"][2]);
  for(auto& elem : j["objects"]){
    if(elem["__type__"] == "sphere"){
      p.add_sphere(Vec3(elem["position"][0],elem["position"][1],elem["position"][2]),elem["radius"]);
    }
  }
  file.close();
  return p;
}

RenderParams parse_params(int argc, char* argv[]){
  cxxopts::Options options("RayTracer","Simple raytracer");
  options.add_options()
          ("w,width","Render width",cxxopts::value<unsigned int>())
          ("h,height","Render height",cxxopts::value<unsigned int>())
          ("s,scene","Scene description file",cxxopts::value<std::string>())
          ("i,image","Image file output",cxxopts::value<std::string>());
  options.parse(argc,argv);
  RenderParams r(options["w"].as<unsigned int>(),options["h"].as<unsigned int>(),options["i"].as<std::string>(),options["s"].as<std::string>());
  return r;
}

void do_render(SceneParams& sceneParams, RenderParams& renderParams){
  std::vector<std::vector<Pixel> > preImage(renderParams.width, std::vector<Pixel>(renderParams.height));
  Camera cam(sceneParams.cam_fov,sceneParams.cam_up,sceneParams.cam_pos,
             sceneParams.cam_target,renderParams.width,renderParams.height);
  for(int i = 0 ; i < preImage.size(); i++){
    for(int j = 0 ; j < preImage[0].size(); j++){
      double i_u = cam.get_left() + ((cam.get_right() - cam.get_left())/renderParams.width)*(i + 0.5);
      double j_v = cam.get_bottom() + ((cam.get_top() - cam.get_bottom())/renderParams.height)*(j + 0.5);
      Vec3 pixDir = cam.get_u() * i_u + cam.get_v() * j_v + cam.get_w() * -0.1; //NEAR ASSUMED 0.1
      Ray pixRay(cam.cam_pos,pixDir);
      bool hit = false;
      for(auto const& sphere : (*sceneParams.scene_objs)){
        Vec3 out;
        if(hit |= pixRay.intersect_sphere(sphere,out)){
          preImage[i][j] = Pixel{0,0,0,255};
        }
      }
      if(!hit){
        preImage[i][j] = Pixel{(unsigned char)(sceneParams.bg_color.x*255),
                               (unsigned char)(sceneParams.bg_color.y*255),
                               (unsigned char)(sceneParams.bg_color.z*255),255};
      }
    }
  }
  unsigned char* img = new unsigned char[renderParams.width * renderParams.height * 4];
  for(int i = 0 ; i < renderParams.width; i++){
    for(int j = 0 ; j < renderParams.height; j++){
      img[(j * renderParams.width + renderParams.width -1 - i)*4 + 0] = preImage[renderParams.width - 1 - i][renderParams.height - 1 - j].R;
      img[(j * renderParams.width + renderParams.width -1 - i)*4 + 1] = preImage[renderParams.width - 1 - i][renderParams.height - 1 - j].G;
      img[(j * renderParams.width + renderParams.width -1 - i)*4 + 2] = preImage[renderParams.width - 1 - i][renderParams.height - 1 - j].B;
      img[(j * renderParams.width + renderParams.width -1 - i)*4 + 3] = preImage[renderParams.width - 1 - i][renderParams.height - 1 - j].A;
    }
  }
  std::cout << "Beggining png encode" << std::endl;
  unsigned error = lodepng_encode32_file(renderParams.img_title.c_str(),img,renderParams.width,renderParams.height);
  std::cout << "Png encode finished" << std::endl;
  if(error) std::cout << lodepng_error_text(error) << std::endl;
  delete img;
}



int main(int argc, char* argv[]) {
  RenderParams renderParams = parse_params(argc, argv);
  SceneParams sceneParams = parse_scene(renderParams);
  do_render(sceneParams, renderParams);
  return 0;
}

