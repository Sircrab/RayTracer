//
// Created by Geno on 14-Oct-17.
//

#ifndef RAYTRACER_TEXTUREFILTERS_H
#define RAYTRACER_TEXTUREFILTERS_H
#include "Color.h"
#include "Texture.h"
#include "Vec2.h"
#include <memory>
class TextureFilter{
public:
  virtual Color get_filtered_color(std::shared_ptr<Texture> texture, const Vec2& uvCoords) const=0;
};

class NearestPointFilter : public TextureFilter{
public:
  Color get_filtered_color(std::shared_ptr<Texture> texture, const Vec2& uvCoords) const override;
};

class BilinearFilter : public TextureFilter{
public:
  Color get_filtered_color(std::shared_ptr<Texture> texture, const Vec2& uvCoords) const override;
};
#endif //RAYTRACER_TEXTUREFILTERS_H
