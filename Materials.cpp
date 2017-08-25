//
// Created by Geno on 25-Aug-17.
//
#include "Materials.h"

Color LambertMaterial::get_color_from(PointLight pointLight) const {return Color(0.0,0.0,0.0);}
Color LambertMaterial::get_color_from(DirectionalLight directionalLight) const {return Color(0.0,0.0,0.0);}
Color LambertMaterial::get_color_from(SpotLight spotLight) const {return Color(0.0,0.0,0.0);}
Color LambertMaterial::get_color_from(AmbientLight ambientLight) const {return Color(0.0,0.0,0.0);}

Color BlinnPhongMaterial::get_color_from(PointLight pointLight) const {return Color(0.0,0.0,0.0);}
Color BlinnPhongMaterial::get_color_from(DirectionalLight directionalLight) const {return Color(0.0,0.0,0.0);}
Color BlinnPhongMaterial::get_color_from(SpotLight spotLight) const {return Color(0.0,0.0,0.0);}
Color BlinnPhongMaterial::get_color_from(AmbientLight ambientLight) const {return Color(0.0,0.0,0.0);}

