//
// Created by gabriel on 10.10.2016.
//

#ifndef GRAPHICSPROJECT_LIGHT_H
#define GRAPHICSPROJECT_LIGHT_H


#include <src/utils/Vectors.h>
#include "src/utils/utils.h"
class PointLight {
private:
    Vector3f position;
    Vector3f color;
    Vector3f specularColor  = Vector3f(1, 1, 1);
    Vector3f attenuation    = Vector3f(1, 0, 0);
public:
    inline PointLight(Vector3f position, Vector3f color) : position(position), color(color){};
    inline PointLight(Vector3f position, Vector3f color, Vector3f attenuation) : position(position), color(color), attenuation(attenuation){};
    inline void setPosition(const float x, const float y, const float z){position.set(x, y, z); };

    inline Vector3f getPosition(void) const{return position; };
    inline Vector3f getDiffuseColor(void)const{return color; };
    inline Vector3f getSpecularColor(void) const{return specularColor; };
    inline Vector3f getAttenuation(void) const{return attenuation; };
};

typedef std::shared_ptr<PointLight> PointerPointLight;

inline PointerPointLight createPointLight(Vector3f position, Vector3f color){
    return PointerPointLight(new PointLight(position, color));
}

inline PointerPointLight createPointLight(Vector3f position, Vector3f color, Vector3f attenuation){
    return PointerPointLight(new PointLight(position, color, attenuation));
}
#endif //GRAPHICSPROJECT_LIGHT_H
