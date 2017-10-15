//
// Created by Geno on 14-Oct-17.
//

#include "TextureFilters.h"

Color NearestPointFilter::get_filtered_color(std::shared_ptr<Texture> texture, const Vec2 &uvCoords) const {
  unsigned int ti = (unsigned int)(uvCoords.x * (texture->width - 1) + 0.5);
  unsigned int tj = (unsigned int)(uvCoords.y * (texture->height - 1) + 0.5);
  Pixel pix = texture->colors[ti][tj];
  return Color(pix.R * 1.0 / 255.0, pix.G * 1.0 / 255.0, pix.B * 1.0 / 255.0);
}

Color BilinearFilter::get_filtered_color(std::shared_ptr<Texture> texture, const Vec2 &uvCoords) const {
  unsigned int ti = (unsigned int)(uvCoords.x * (texture->width - 1));
  unsigned int tj = (unsigned int)(uvCoords.y * (texture->height - 1));
  double i = uvCoords.x * (texture->width - 1);
  double j = uvCoords.y * (texture->height - 1);
  double di = i - ti;
  double dj = j - tj;
  Color colorA = texture->colors[ti][tj].to_color() * (1-di) + texture->colors[std::min(texture->width-1,ti+1)][tj].to_color()*(di);
  Color colorB = texture->colors[ti][std::min(texture->height -1,tj+1)].to_color() * (1-di) +
    texture->colors[std::min(texture->width-1,ti+1)][std::min(texture->height -1,tj+1)].to_color()*(di);
  return colorA * (1-dj) + colorB * (dj);
}