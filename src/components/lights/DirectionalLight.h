//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_DIRICTIONALLIGHT_H
#define GRAPHICSPROJECT_DIRICTIONALLIGHT_H


#include <src/utils/GTypes.h>
#include <src/utils/Vectors.h>

class DirectionalLight {
private:
    Vector3f diffuseColor;
    Vector3f specularColor = Vector3f(1, 1, 1);
    Vector3f direction;

    inline DirectionalLight(Vector3f diffuseColor, Vector3f dir) : DirectionalLight(diffuseColor, specularColor, dir){};

    inline DirectionalLight(Vector3f diffuseColor, Vector3f specularColor, Vector3f di) :
            diffuseColor(diffuseColor),
            specularColor(specularColor),
            direction(di){
    }
public:
    inline Vector3f getDirection(void) const{return direction; }
    inline Vector3f getDiffuseColor(void) const{return diffuseColor; }
    inline Vector3f getSpecularColor(void) const{return specularColor; }

    inline static PointerDirectionalLight create(Vector3f diffuseColor, Vector3f direction){
        return PointerDirectionalLight(new DirectionalLight(diffuseColor, direction));
    }
    inline static PointerDirectionalLight create(Vector3f diffuseColor, Vector3f specularColor, Vector3f direction){
        return PointerDirectionalLight(new DirectionalLight(diffuseColor, specularColor, direction));
    }
    inline LightData getData(void) const{
        return {LightTypes::DIRECTIONAL, {0, 0, 0}, getDiffuseColor().getVec(), getSpecularColor().getVec(), {1, 0, 0}, direction.getVec(), 0, 0};
    }
    inline void setDirection(Vector3f dir){direction = dir; };
};



#endif //GRAPHICSPROJECT_DIRICTIONALLIGHT_H
