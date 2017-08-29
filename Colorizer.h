//
// Created by Geno on 29-Aug-17.
//

#ifndef RAYTRACER_COLORIZER_H
#define RAYTRACER_COLORIZER_H
#include "SceneParams.h"
#include "SceneMaterials.h"
#include "RenderParams.h"
#include "Color.h"
//Colorizer must exist only within the context of a renderer
class Colorizer {
public:
    SceneParams& sceneParams;
    SceneMaterials& sceneMaterials;
    RenderParams& renderParams;
    Colorizer(SceneParams& sceneParams, SceneMaterials& sceneMaterials, RenderParams& renderParams) :
            sceneParams(sceneParams), sceneMaterials(sceneMaterials), renderParams(renderParams){};
    Color get_color(const SceneObject& obj,const Vec3& hitPoint, unsigned int depth);
private:
    Color get_direct_color(const SceneObject& obj,const Vec3& hitPoint);
    Color get_indirect_color(const SceneObject& obj);
    Color get_reflected_color(const SceneObject& obj,const Vec3& hitPoint, unsigned int depth);
    Color get_refracted_color(const SceneObject& obj,const Vec3& hitPoint, unsigned int depth);
};
#endif //RAYTRACER_COLORIZER_H
