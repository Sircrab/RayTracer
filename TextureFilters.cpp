//
// Created by Geno on 14-Oct-17.
//

#include "TextureFilters.h"

Color NearestPointFilter::get_filtered_color(std::shared_ptr<Texture> texture, const Vec2 &uvCoords) const {
  return Color(0.0, 0.0, 0.0);
}

Color BilinearFilter::get_filtered_color(std::shared_ptr<Texture> texture, const Vec2 &uvCoords) const {
  //TODO: Finish this
  return Color(0.0,0.0,0.0);
}