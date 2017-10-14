//
// Created by Geno on 14-Oct-17.
//

#include "Pixel.h"

Color Pixel::to_color(){
  return Color(R * 1.0 / 255.0, G * 1.0 / 255.0, B * 1.0 / 255.0);
}