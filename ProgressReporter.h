//
// Created by Geno on 05-Oct-17.
//
#include <mutex>

#ifndef RAYTRACER_PROGRESSREPORTER_H
#define RAYTRACER_PROGRESSREPORTER_H
class ProgressReporter{
public:
  unsigned int totalTasks;
  std::mutex innerMutex;
  unsigned int cnt = 0;
  bool keepReporting = true;
  unsigned int lastPercentage = 0;
  ProgressReporter(unsigned int totalTasks) : totalTasks(totalTasks){};
  ProgressReporter() : totalTasks(0){};
  void atomic_increase();
  void report();
};
#endif //RAYTRACER_PROGRESSREPORTER_H
