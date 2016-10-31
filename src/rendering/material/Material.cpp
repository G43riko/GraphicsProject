//
// Created by gabriel on 24.9.2016.
//

#include "Material.h"

PointerMaterial createMaterial(PointerTexture2D texture){
    return PointerMaterial(new Material(texture));
}
PointerMaterial createMaterial(PointerTexture2D texture, PointerTexture2D normal){
    return PointerMaterial(new Material(texture, normal));
}

Material::Material(PointerTexture2D diffuse){
    this -> diffuse = diffuse;
}

Material::Material(PointerTexture2D diffuse, PointerTexture2D normal){
    this -> diffuse = diffuse;
    this -> normal = normal;
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