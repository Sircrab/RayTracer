//
// Created by Geno on 29-Aug-17.
//

#ifndef RAYTRACER_PIXEL_H
#define RAYTRACER_PIXEL_H
#include "Color.h"
struct Pixel{
  unsigned char R;
  unsigned char G;
  unsigned char B;
  unsigned char A;
  Color to_color();
};

#endif //RAYTRACER_PIXEL_H
