//
// Created by Geno on 29-Aug-17.
//

#ifndef RAYTRACER_COLORIZER_H
#define RAYTRACER_COLORIZER_H
#include "SceneParams.h"
#include "SceneMaterials.h"
#include "RenderParams.h"
#include "Color.h"
#include "Ray.h"
//Colorizer must exist only within the context of a renderer
class Colorizer {
public:
    SceneParams& sceneParams;
    SceneMaterials& sceneMaterials;
    RenderParams& renderParams;
    Colorizer(SceneParams& sceneParams, SceneMaterials& sceneMaterials, RenderParams& renderParams) :
            sceneParams(sceneParams), sceneMaterials(sceneMaterials), renderParams(renderParams){};
    Color get_color(const SceneObject& obj,const Vec3& hitPoint, const Vec3& originPoint, unsigned int depth);
    bool get_closest_object(const Ray& hitRay, Vec3& outPos, std::shared_ptr<const SceneObject>& outObj);
private:
    const double eps = 1e-5; //Shadow bias
    Color get_direct_color(const SceneObject& obj,const Vec3& hitPoint, const Vec3& originPoint);
    Color get_indirect_color(const SceneObject& obj);
    Color get_reflected_color(const SceneObject& obj,const Vec3& hitPoint,const Vec3& originPoint, unsigned int depth);
    Color get_refracted_color(const SceneObject& obj,const Vec3& hitPoint, unsigned int depth);
    bool in_shadow(const Vec3& hitPoint,const Light& light);
};
#endif //RAYTRACER_COLORIZER_H
