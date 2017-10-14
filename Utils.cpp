//
// Created by Geno on 29-Aug-17.
//
#include "Utils.h"
#include "lodepng/lodepng.h"
#include <memory>
#include <iostream>
void utils:: generateImage(std::string name, std::vector<std::vector<Pixel> >& preImage, unsigned width, unsigned height){
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



