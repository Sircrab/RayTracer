//
// Created by Geno on 05-Oct-17.
//

#include <iostream>
#include "ProgressReporter.h"

void ProgressReporter::atomic_increase() {
  std::lock_guard<std::mutex> lock(innerMutex);
  cnt++;
}

void ProgressReporter::report(){
  unsigned int percent = (unsigned int)((cnt*1.0/totalTasks*1.0)*100);
  if(percent != lastPercentage){
    std::cout << "\r" << percent << "%";
    std::cout.flush();
    lastPercentage = percent;
  }

}