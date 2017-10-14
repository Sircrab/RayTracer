//
// Created by Geno on 25-Aug-17.
//
#include "Renderer.h"
#include "Utils.h"
#include "ProgressReporter.h"
#include <thread>
#include <iostream>
#include <cmath>
#include <chrono>


void Renderer::do_render() {
  auto preImage = std::make_shared<std::vector<std::vector<Pixel> > > (renderParams->width, std::vector<Pixel>(renderParams->height));
  auto cam = std::make_shared<Camera>(sceneParams->camFov,sceneParams->camUp,sceneParams->camPos,
             sceneParams->camTarget,renderParams->width,renderParams->height);
  auto colorizer = std::make_shared<Colorizer>(sceneParams,sceneMaterials,renderParams);
  std::vector<std::thread > threadPool;
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  for(unsigned int i = 0 ; i < preImage->size(); i+= renderParams->taskSize){
    for(unsigned int j = 0 ; j < (*preImage)[0].size(); j+= renderParams->taskSize){
      std::shared_ptr<RenderTask> task = std::make_shared<RenderTask>
        (i, std::min<unsigned int>(i + renderParams->taskSize, preImage->size()),
         j, std::min<unsigned int>(j + renderParams->taskSize, (*preImage)[0].size()),
         colorizer, preImage, cam);
      taskQueue.push(task);
    }
  }
  reporter = std::make_shared<ProgressReporter>(taskQueue.size());
  std::thread reporterThread = std::thread(report_progress, this);
  for(int i = 0 ; i < renderParams->numThreads; i++){
    threadPool.push_back(std::thread(thread_render, this));
  }
  for(auto& thread: threadPool){
    thread.join();
  }
  end = std::chrono::system_clock::now();
  reporter->keepReporting = false;
  reporterThread.join();
  std::cout << std::endl;
  std::chrono::duration<double> elapsedSeconds = end-start;
  std::cout << "Duration: " << elapsedSeconds.count() << std::endl;

  utils::generateImage(renderParams->img_title,*preImage,renderParams->width,renderParams->height);
}

void Renderer::thread_render() {

  while(true){
    std::shared_ptr<RenderTask> nextTask = pop_task_atomic();
    if(nextTask == nullptr) break;
    for(unsigned int i = nextTask->fromX; i < nextTask->toX; i++){
      for(unsigned int j = nextTask->fromY; j < nextTask->toY; j++){
        nextTask->render_pixel_at(i,j);
      }
    }
    reporter->atomic_increase();
  }

}

void Renderer::report_progress() {
  while(reporter->keepReporting){
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    reporter->report();
  }
}

std::shared_ptr<RenderTask> Renderer::pop_task_atomic() {
  std::lock_guard<std::mutex> guard(queueMutex);
  std::shared_ptr<RenderTask> nextTask = nullptr;
  if(!taskQueue.empty()){
    nextTask = taskQueue.front();
    taskQueue.pop();
  }
  return nextTask;
}



