//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_DIRICTIONALLIGHT_H
#define GRAPHICSPROJECT_DIRICTIONALLIGHT_H


#include <src/utils/Vectors.h>

class DirectionalLight {
private:
    Vector3f diffuseColor;
    Vector3f specularColor = Vector3f(1, 1, 1);
    Vector3f direction;
public:
    DirectionalLight(Vector3f diffuseColor, Vector3f dir) : DirectionalLight(diffuseColor, specularColor, dir){};

    DirectionalLight(Vector3f diffuseColor, Vector3f specularColor, Vector3f di) :
            diffuseColor(diffuseColor),
            specularColor(specularColor),
            direction(di){
    }
    Vector3f getDirection(void){
        return direction;
    }
    Vector3f getDiffuseColor(void){
        return diffuseColor;
    }
    Vector3f getSpecularColor(void){
        return specularColor;
    }
};

typedef std::shared_ptr<DirectionalLight> PointerDirectionalLight;

PointerDirectionalLight createDirectionalLight(Vector3f diffuseColor, Vector3f direction);
PointerDirectionalLight createDirectionalLight(Vector3f diffuseColor, Vector3f specularColor, Vector3f direction);


#endif //GRAPHICSPROJECT_DIRICTIONALLIGHT_H
