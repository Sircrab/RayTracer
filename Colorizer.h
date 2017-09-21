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
#include "RayCastHit.h"
#include <memory>
//Colorizer must exist only within the context of a renderer
class Colorizer {
public:
  std::shared_ptr<const SceneParams> sceneParams;
  std::shared_ptr<const SceneMaterials> sceneMaterials;
  std::shared_ptr<const RenderParams> renderParams;
  Colorizer(std::shared_ptr<const SceneParams> sceneParams,
            std::shared_ptr<const SceneMaterials> sceneMaterials,
            std::shared_ptr<const RenderParams> renderParams) :
          sceneParams(sceneParams), sceneMaterials(sceneMaterials), renderParams(renderParams){};
  Color get_color(const SceneObject &obj, const RayCastHit &rayHit, const Vec3 &originPoint, unsigned int depth);
  bool get_closest_object(const Ray &hitRay, RayCastHit &rayHit, std::shared_ptr<const SceneObject> &outObj);
private:
  const double eps = 1e-6; //Shadow bias
  Color get_direct_color(const SceneObject &obj, const RayCastHit &rayHit, const Vec3 &originPoint);
  Color get_indirect_color(const SceneObject& obj);
  Color get_reflected_color(const SceneObject &obj, const RayCastHit &rayHit, const Vec3 &originPoint,
                            unsigned int depth);
  Color get_refracted_color(const SceneObject &obj, const RayCastHit &rayHit, const Vec3 &originPoint,
                            unsigned int depth);
  bool in_shadow(const Vec3& hitPoint,const Light& light);
  double total_internal_reflection_coef(const Vec3& normal, const Vec3& eyeDir, double rIdxIn, double rIdxOut) const;
  Vec3 get_refraction_deviation(const Vec3& normal, const Vec3& eyeDir, double rIdxIn, double rIdxOut) const;
  double fresnel_coef(double rIdxIn, double rIdxOut, double angleCosine) const;
  bool refract(const Vec3& entryDir, const Vec3& normal, const Vec3& hitPoint, double entryIdx, double exitIdx, Ray& out) const;
  Ray reflect(const Vec3& hitPoint, const Vec3& originPoint, const Vec3& normal) const;
};
#endif //RAYTRACER_COLORIZER_H
