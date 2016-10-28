//
// Created by gabriel on 24.9.2016.
//

#include "Material.h"

PointerMaterial createMaterial(PointerTexture2D texture){
    return PointerMaterial(new Material(texture));
}

Material::Material(PointerTexture2D diffuse){
    this -> diffuse = diffuse;
}
PointerTexture2D Material::getDiffuse(void){
    return diffuse;
}

PointerTexture2D Material::getNormal(void){
    return normal;
}

PointerTexture2D Material::getSpecular(void){
    return specular;
}
PointerTexture2D Material::getAlpha(void){
    return alpha;
}