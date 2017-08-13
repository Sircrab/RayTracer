#include <iostream>
#include <vector>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "SceneParams.h"
#include "RenderParams.h"
#include "Camera.h"
#include "lodepng/lodepng.h"

struct Pixel{
  unsigned char R;
  unsigned char G;
  unsigned char B;
  unsigned char A;
};

SceneParams parse_scene(){
  SceneParams p;
  p.cam_fov = 45;
  p.cam_pos = Vec3(5,5,5);
  p.cam_up = Vec3(0,1,0);
  p.cam_target = Vec3(0.5,0.5,-0.5);
  p.bg_color = Vec3(1,1,1);
  p.add_sphere(Vec3(0,0,0),1);
  p.add_sphere(Vec3(1.2,1.2,0),0.5);
  p.add_sphere(Vec3(-1.5,0,0),0.3);
  return p;
}

RenderParams parse_params(){
  RenderParams r(256,128,"meme.png","meme");
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
        preImage[i][j] = Pixel{255,255,255,255};
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
}



int main() {
  RenderParams renderParams = parse_params();
  SceneParams sceneParams = parse_scene();
  do_render(sceneParams, renderParams);
  return 0;
}

