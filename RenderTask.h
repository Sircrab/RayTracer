//
// Created by Geno on 18-Sep-17.
//


#ifndef RAYTRACER_RENDERTASK_H
#define RAYTRACER_RENDERTASK_H
#include "Colorizer.h"
#include "Pixel.h"
#include "Camera.h"
#include "ProgressReporter.h"
#include <memory>
#include <vector>
class RenderTask{
public:
  unsigned int fromX, toX, fromY, toY;
  std::shared_ptr<Colorizer> colorizer;
  std::shared_ptr<std::vector<std::vector<Pixel> > > preImg;
  std::shared_ptr<Camera> camera;
  RenderTask(unsigned int fromX, unsigned int toX, unsigned int fromY, unsigned int toY,
             std::shared_ptr<Colorizer> colorizer, std::shared_ptr<std::vector<std::vector<Pixel> > > preImg,
             std::shared_ptr<Camera> camera) :
    fromX(fromX), toX(toX), fromY(fromY), toY(toY), colorizer(colorizer), preImg(preImg), camera(camera){};
  void render_pixel_at(unsigned int x, unsigned int y);
};
#endif //RAYTRACER_RENDERTASK_H
