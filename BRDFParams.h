//
// Created by Geno on 14-Oct-17.
//

#ifndef RAYTRACER_BRDFPARAMS_H
#define RAYTRACER_BRDFPARAMS_H
struct BRDFParams{
  bool isAmbient;
  double shininess;
  BRDFParams(bool isAmbient): isAmbient(isAmbient){};
  BRDFParams(bool isAmbient, double shininess) : isAmbient(isAmbient), shininess(shininess){};
};
#endif //RAYTRACER_BRDFPARAMS_H
