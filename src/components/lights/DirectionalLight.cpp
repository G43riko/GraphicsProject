//
// Created by gabriel on 14.1.2017.
//

#include "DirectionalLight.h"

PointerDirectionalLight createDirectionalLight(Vector3f diffuseColor, Vector3f direction){
    return PointerDirectionalLight(new DirectionalLight(diffuseColor, direction));
}
PointerDirectionalLight createDirectionalLight(Vector3f diffuseColor, Vector3f specularColor, Vector3f direction){
    return PointerDirectionalLight(new DirectionalLight(diffuseColor, specularColor, direction));
}
