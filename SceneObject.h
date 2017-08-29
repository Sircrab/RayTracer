//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_SCENEOBJECT_H
#define RAYTRACER_SCENEOBJECT_H
#include "Sphere.h"
#include "Materials.h"
#include "Color.h"
#include <vector>
#include <memory>

class SceneObject{
public:
    Sphere sphere;
    std::vector<std::shared_ptr<const BRDFMaterial> > brdfMats;
    std::vector<std::shared_ptr<const ReflectiveMaterial> > reflectiveMats;
    std::vector<std::shared_ptr<const DielectricMaterial> > dielectricMats;
    Color ambientColor = Color(0.0,0.0,0.0);
    SceneObject(Sphere sphere): sphere(sphere){};
    void attach_brdf_material(std::shared_ptr<const BRDFMaterial> m);
    void attach_reflective_material(std::shared_ptr<const ReflectiveMaterial> m);
    void attach_dielectric_material(std::shared_ptr<const DielectricMaterial> m);
};
#endif //RAYTRACER_SCENEOBJECT_H
