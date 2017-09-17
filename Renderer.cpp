//
// Created by Geno on 25-Aug-17.
//
#include "Renderer.h"
#include "Camera.h"
#include "Ray.h"
#include "Colorizer.h"
#include "Pixel.h"
#include "Utils.h"
#include <iostream>

void Renderer::do_render() {
  std::vector<std::vector<Pixel> > preImage(renderParams.width, std::vector<Pixel>(renderParams.height));
  Camera cam(sceneParams.camFov,sceneParams.camUp,sceneParams.camPos,
             sceneParams.camTarget,renderParams.width,renderParams.height);
  Colorizer colorizer(sceneParams,sceneMaterials,renderParams);
  for(int i = 0 ; i < preImage.size(); i++){
    for(int j = 0 ; j < preImage[0].size(); j++){
      double i_u = cam.get_left() + ((cam.get_right() - cam.get_left())/renderParams.width)*(i + 0.5);
      double j_v = cam.get_bottom() + ((cam.get_top() - cam.get_bottom())/renderParams.height)*(j + 0.5);
      Vec3 pixDir = cam.get_u() * i_u + cam.get_v() * j_v + cam.get_w() * -near;
      Ray pixRay(cam.cam_pos,pixDir);
      Color finalColor;
      Vec3 out;
      std::shared_ptr<const SceneObject> closestObj = nullptr;
      bool hit = colorizer.get_closest_object(pixRay, out,closestObj);
      if(hit){
        finalColor = colorizer.get_color(*closestObj,out, sceneParams.camPos, 0);
      } else {
       finalColor = sceneParams.bgColor;
      }
      preImage[i][j] = Pixel{(unsigned char)(finalColor.r()*255),
                             (unsigned char)(finalColor.g()*255),
                             (unsigned char)(finalColor.b()*255),255};
    }
  }
  utils::generateImage(renderParams.img_title,preImage,renderParams.width,renderParams.height);
}

