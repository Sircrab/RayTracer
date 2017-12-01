//
// Created by Geno on 29-Aug-17.
//
#include "Utils.h"
#include "lodepng/lodepng.h"
#include <memory>
#include <iostream>
#include <cmath>
#include "Mat3x3.h"
double Utils::exposureTime = 0.0;

void Utils:: generateImage(std::string name, std::vector<std::vector<Pixel> >& preImage, unsigned width, unsigned height){
    auto img = std::make_shared<std::vector<unsigned char> >(width * height * 4);
    for(int i = 0 ; i < width; i++){
      for(int j = 0 ; j < height; j++){
        (*img)[(j * width + width -1 - i)*4 + 0] = preImage[width - 1 - i][height - 1 - j].R;
        (*img)[(j * width + width -1 - i)*4 + 1] = preImage[width - 1 - i][height - 1 - j].G;
        (*img)[(j * width + width -1 - i)*4 + 2] = preImage[width - 1 - i][height - 1 - j].B;
        (*img)[(j * width + width -1 - i)*4 + 3] = preImage[width - 1 - i][height - 1 - j].A;
      }
    }
    unsigned error = lodepng::encode(name,*img,width,height);
    if(error) std::cerr << lodepng_error_text(error) << std::endl;
  }

float Utils::get_rand() {
  return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - 0.5f;
}


double Utils::get_rand_time() {
  float randomValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  return (exposureTime * randomValue);
}

Vec3 Utils::get_rand_dir(Vec3 normal) {
  Vec3 result;
  Vec3 natNormal = normal.normalize();
  while(natNormal.dot(result) <= 0){
    double ranFirst = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2) - 1.0;
    double ranSecond = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2) - 1.0;
    double ranThird = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2) - 1.0;
    result = Vec3(ranFirst,ranSecond,ranThird).normalize();
  }
  return result;

}


