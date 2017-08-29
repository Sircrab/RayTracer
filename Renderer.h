//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H
#include "SceneMaterials.h"
#include "SceneParams.h"
#include "RenderParams.h"
#include <memory>
struct Pixel{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};

class Renderer{
public:
    SceneParams sceneParams;
    SceneMaterials sceneMaterials;
    RenderParams renderParams;
    Renderer(SceneParams sceneParams, SceneMaterials sceneMaterials ,RenderParams renderParams) :
            sceneParams(sceneParams),sceneMaterials(sceneMaterials),renderParams(renderParams){};
    void do_render();
private:
    static constexpr double near = 0.1;
};
#endif //RAYTRACER_RENDERER_H
