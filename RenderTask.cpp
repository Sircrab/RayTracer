//
// Created by Geno on 18-Sep-17.
//
#include "RenderTask.h"

void RenderTask::render_pixel_at(unsigned int x, unsigned int y) {
  double i_u = camera->get_left() + ((camera->get_right() - camera->get_left())/colorizer->renderParams->width)*(x + 0.5);
  double j_v = camera->get_bottom() + ((camera->get_top() - camera->get_bottom())/colorizer->renderParams->height)*(y + 0.5);
  Vec3 pixDir = camera->get_u() * i_u + camera->get_v() * j_v + camera->get_w() * -near;
  Ray pixRay(camera->cam_pos,pixDir);
  Color finalColor;
  Vec3 out;
  std::shared_ptr<const SceneObject> closestObj = nullptr;
  bool hit = colorizer->get_closest_object(pixRay, out,closestObj);
  if(hit){
    finalColor = colorizer->get_color(*closestObj,out, camera->cam_pos, 0);
  } else {
    finalColor = colorizer->sceneParams->bgColor;
  }
  (*preImg)[x][y] = Pixel{(unsigned char)(finalColor.r()*255),
                         (unsigned char)(finalColor.g()*255),
                         (unsigned char)(finalColor.b()*255),255};
}
