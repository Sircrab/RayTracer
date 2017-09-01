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
    const double eps = 1e-3; //Shadow bias
    Color get_direct_color(const SceneObject& obj,const Vec3& hitPoint, const Vec3& originPoint);
    Color get_indirect_color(const SceneObject& obj);
    Color get_reflected_color(const SceneObject& obj,const Vec3& hitPoint,const Vec3& originPoint, unsigned int depth);
    Color get_refracted_color(const SceneObject& obj,const Vec3& hitPoint,const Vec3& originPoint, unsigned int depth);
    bool in_shadow(const Vec3& hitPoint,const Light& light);
    double total_internal_reflection_coef(const Vec3& normal, const Vec3& eyeDir, double rIdxIn, double rIdxOut);
    Vec3 get_refraction_deviation(const Vec3& normal, const Vec3& eyeDir, double rIdxIn, double rIdxOut);
    double fresnel_coef(double rIdxIn, double rIdxOut, double angleCosine);
    bool refract(const Vec3& entryDir, const Vec3& normal, const Vec3& hitPoint, double entryIdx, double exitIdx, Ray& out);
};
#endif //RAYTRACER_COLORIZER_H
