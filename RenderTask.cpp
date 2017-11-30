//
// Created by Geno on 18-Sep-17.
//
#include "RenderTask.h"

void RenderTask::render_pixel_at(unsigned int x, unsigned int y) {
  int sampleSize = (int)std::sqrt(colorizer->renderParams->pixelSamples);
  Vec3 colorSum;
  for(int i = 0; i < sampleSize; i++){
    for(int j = 0; j < sampleSize; j++){
      double i_u = camera->get_left() + ((camera->get_right() - camera->get_left())/colorizer->renderParams->width)*(x + (i * 1.0 / sampleSize));
      double j_v = camera->get_bottom() + ((camera->get_top() - camera->get_bottom())/colorizer->renderParams->height)*(y + (j * 1.0 / sampleSize));
      Vec3 dirIJ = camera->get_u() * i_u + camera->get_v() * j_v + camera->get_w() * -camera->get_near();
      Vec3 focalPoint = camera->get_orig_position() + dirIJ;
      Vec3 curCameraPos = camera->get_position();
      Vec3 pixDir = (focalPoint - curCameraPos);
      Ray pixRay(curCameraPos,pixDir);
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
