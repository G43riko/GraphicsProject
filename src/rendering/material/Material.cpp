//
// Created by gabriel on 24.9.2016.
//

#include "Material.h"

Material::Material(Texture2D * diffuse){
    this -> diffuse = diffuse;
}
Texture2D * Material::getDiffuse(void){
    return diffuse;
}