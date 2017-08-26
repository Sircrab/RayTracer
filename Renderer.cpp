//
// Created by Geno on 25-Aug-17.
//
#include "Renderer.h"
#include "Camera.h"
#include "Ray.h"
#include "lodepng/lodepng.h"
#include <iostream>

void Renderer::do_render(SceneParams &sceneParams, RenderParams &renderParams, SceneMaterials &sceneMaterials) {
  double near = 0.1; //NEAR ASSUMED 0.1
  std::vector<std::vector<Pixel> > preImage(renderParams.width, std::vector<Pixel>(renderParams.height));
  Camera cam(sceneParams.cam_fov,sceneParams.cam_up,sceneParams.cam_pos,
             sceneParams.cam_target,renderParams.width,renderParams.height);
  //ORDER THE OBJECTS
  Color bgColor(sceneParams.bg_color.x,sceneParams.bg_color.y,sceneParams.bg_color.z);
  for(int i = 0 ; i < preImage.size(); i++){
    for(int j = 0 ; j < preImage[0].size(); j++){
      double i_u = cam.get_left() + ((cam.get_right() - cam.get_left())/renderParams.width)*(i + 0.5);
      double j_v = cam.get_bottom() + ((cam.get_top() - cam.get_bottom())/renderParams.height)*(j + 0.5);
      Vec3 pixDir = cam.get_u() * i_u + cam.get_v() * j_v + cam.get_w() * -near;
      Ray pixRay(cam.cam_pos,pixDir);
      Color finalColor, directColor, indirectColor;
      bool hit = false;
      for(auto const& curObj : sceneParams.sceneObjs){
        Vec3 out;
        if(hit |= pixRay.intersect_sphere(curObj->sphere,out)){
          for(auto const& light : sceneParams.sceneLights){
            for(auto const& mat : curObj->materials){
              directColor += light->cast_on(*mat,cam,curObj->sphere,out);
            }
          }
          if(sceneParams.sceneAmbientLight != nullptr){
            indirectColor = curObj->ambientColor * sceneParams.sceneAmbientLight->color;
          } else {
            indirectColor = Color(0.0,0.0,0.0);
          }
          finalColor = directColor + indirectColor;
          break;
        }
      }
      if(!hit){
       finalColor = bgColor;
      }
      preImage[i][j] = Pixel{(unsigned char)(finalColor.r()*255),
                             (unsigned char)(finalColor.g()*255),
                             (unsigned char)(finalColor.b()*255),255};
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
  //THIS IS THE C VERSION, PLEASE CHANGE
  unsigned error = lodepng_encode32_file(renderParams.img_title.c_str(),img,renderParams.width,renderParams.height);
  std::cout << "Png encode finished" << std::endl;
  if(error) std::cout << lodepng_error_text(error) << std::endl;
  delete img;
}

