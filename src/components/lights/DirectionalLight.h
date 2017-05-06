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
public:
    inline DirectionalLight(Vector3f diffuseColor, Vector3f dir) : DirectionalLight(diffuseColor, specularColor, dir){};

    inline DirectionalLight(Vector3f diffuseColor, Vector3f specularColor, Vector3f di) :
            diffuseColor(diffuseColor),
            specularColor(specularColor),
            direction(di){
    }
    inline Vector3f getDirection(void) const{return direction; }
    inline Vector3f getDiffuseColor(void) const{return diffuseColor; }
    inline Vector3f getSpecularColor(void) const{return specularColor; }
};


inline PointerDirectionalLight createDirectionalLight(Vector3f diffuseColor, Vector3f direction){
    return PointerDirectionalLight(new DirectionalLight(diffuseColor, direction));
}
inline PointerDirectionalLight createDirectionalLight(Vector3f diffuseColor, Vector3f specularColor, Vector3f direction){
    return PointerDirectionalLight(new DirectionalLight(diffuseColor, specularColor, direction));
}
#endif //GRAPHICSPROJECT_DIRICTIONALLIGHT_H
