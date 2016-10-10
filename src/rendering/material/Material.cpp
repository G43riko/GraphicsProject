//
// Created by gabriel on 24.9.2016.
//

#include "Material.h"

Material::Material(PointerTexture2D diffuse){
    this -> diffuse = diffuse;
}
PointerTexture2D Material::getDiffuse(void){
    return diffuse;
}