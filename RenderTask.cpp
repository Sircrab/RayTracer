//
// Created by Geno on 18-Sep-17.
//
#include "RenderTask.h"
#include <cmath>
#include <iostream>

void RenderTask::render_pixel_at(unsigned int x, unsigned int y) {
  double leftI_u = camera->get_left() + ((camera->get_right() - camera->get_left())/colorizer->renderParams->width)*(x);
  double rightI_u = camera->get_left() + ((camera->get_right() - camera->get_left())/colorizer->renderParams->width)*(x + 1.0);
  double bottomJ_v = camera->get_bottom() + ((camera->get_top() - camera->get_bottom())/colorizer->renderParams->height)*(y);
  double topJ_v = camera->get_bottom() + ((camera->get_top() - camera->get_bottom())/colorizer->renderParams->height)*(y + 1.0);

  Vec3 bottomLeftPixDir = camera->get_u() * leftI_u + camera->get_v() * bottomJ_v + camera->get_w() * -near;
  int sampleSize = (int)std::sqrt(colorizer->renderParams->pixelSamples);
  Vec3 horizDist = (camera->get_u() * rightI_u - camera->get_u()*leftI_u) * (1.0/sampleSize);
  Vec3 vertDist = (camera->get_v() * topJ_v - camera->get_v()*bottomJ_v) * (1.0/sampleSize);
  Vec3 colorSum;
  for(int i = 0; i < sampleSize; i++){
    for(int j = 0; j < sampleSize; j++){
      Vec3 pixDir = bottomLeftPixDir + horizDist * i + vertDist * j;
      Ray pixRay(camera->cam_pos,pixDir);
      RayCastHit rayHit;
      std::shared_ptr<const SceneObject> closestObj = nullptr;
      bool hit = colorizer->get_closest_object(pixRay, rayHit,closestObj);
      if(hit){
        colorSum += colorizer->get_color(*closestObj,rayHit, camera->cam_pos, 0).to_Vec3();
      } else {
        colorSum += colorizer->sceneParams->bgColor.to_Vec3();
      }
    }
  }
  colorSum = colorSum * (1.0/(sampleSize * sampleSize));
  Color finalColor(colorSum.x, colorSum.y, colorSum.z);
  (*preImg)[x][y] = Pixel{(unsigned char)(finalColor.r()*255),
                         (unsigned char)(finalColor.g()*255),
                         (unsigned char)(finalColor.b()*255),255};
}
