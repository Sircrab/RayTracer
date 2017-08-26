//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H
#include "SceneMaterials.h"
#include "SceneParams.h"
#include "RenderParams.h"
struct Pixel{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};

class Renderer{
public:
    static void do_render(SceneParams& sceneParams, RenderParams& renderParams, SceneMaterials& sceneMaterials);
};
#endif //RAYTRACER_RENDERER_H
