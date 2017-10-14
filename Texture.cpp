//
// Created by Geno on 13-Oct-17.
//
#include <iostream>
#include <fstream>
#define cimg_use_jpeg
#include "CImg/CImg.h"
#include "lodepng/lodepng.h"
#include "Texture.h"

void Texture::build_from_file(const std::string& fileName){
  auto dotIdx = fileName.find(".");
  extension = fileName.substr(dotIdx + 1,fileName.size() - dotIdx - 1);
  if(extension == "png"){
    read_png(fileName);
  } else if(extension == "jpg" || extension == "jpeg"){
    read_jpg(fileName);
  }
}

void Texture::read_png(const std::string& fileName){
  std::vector<unsigned char> png;
  unsigned error = lodepng::decode(png, width, height, fileName.c_str());
  if(error){
    std::cout << "PNG decoder error" << std::endl;
  }
  for(int row = 0 ; row < height; row++){
    for(int col = 0 ; col < width; col++){
      unsigned char r = png[(row * width * 4) + (col * 4) + 0];
      unsigned char g = png[(row * width) + (col * 4) + 1];
      unsigned char b = png[(row * width) + (col * 4) + 2];
      unsigned char a = png[(row * width) + (col * 4) + 3];
      colors[col][row] = Pixel{r,g,b,a};
    }
  }
}

void Texture::read_jpg(const std::string& fileName){
  cimg_library::CImg<unsigned char> img(fileName.c_str());
  width = (unsigned int)img.width();
  height = (unsigned int)img.height();
  colors = std::vector< std::vector<Pixel> >(width, std::vector<Pixel>(height));
  for(int row = 0 ; row < height; row++){
    for(int col = 0; col < width; col++){
      unsigned char r = img(col,row,0,0);
      unsigned char g = img(col, row, 0, 1);
      unsigned char b = img(col, row, 0 , 2);
      colors[col][row] = Pixel{r,g,b,255};
    }
  }
}