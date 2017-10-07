//
// Created by Geno on 25-Aug-17.
//

#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H
#include "SceneMaterials.h"
#include "SceneParams.h"
#include "RenderParams.h"
#include "RenderTask.h"
#include <memory>
#include <queue>
#include <mutex>
class Renderer{
public:
  std::shared_ptr<const SceneParams> sceneParams;
  std::shared_ptr<const SceneMaterials> sceneMaterials;
  std::shared_ptr<const RenderParams> renderParams;
  std::shared_ptr<ProgressReporter> reporter;
  Renderer(std::shared_ptr<const SceneParams> sceneParams,
           std::shared_ptr<const SceneMaterials> sceneMaterials,
           std::shared_ptr<const RenderParams> renderParams) :
          sceneParams(sceneParams),sceneMaterials(sceneMaterials),renderParams(renderParams),
          taskQueue(std::queue<std::shared_ptr<RenderTask> >()), queueMutex(){};
  void do_render();
private:
  std::queue<std::shared_ptr<RenderTask> > taskQueue;
  std::mutex queueMutex;
  void thread_render();
  std::shared_ptr<RenderTask> pop_task_atomic();
  void report_progress();
};
#endif //RAYTRACER_RENDERER_H
