//
// Created by gabriel on 10.10.2016.
//

#ifndef GRAPHICSPROJECT_LIGHT_H
#define GRAPHICSPROJECT_LIGHT_H


#include <src/utils/Vectors.h>
#include <src/utils/GTypes.h>
#include "src/utils/GUtils.h"
class PointLight {
private:
    Vector3f position;
    Vector3f diffuseColor;
    Vector3f specularColor  = Vector3f(0.5f, 0.5f, 0.5f);
    Vector3f attenuation    = Vector3f(1, 0, 0);
protected:
    inline PointLight(Vector3f position, Vector3f color) : position(position), diffuseColor(color){};
    inline PointLight(Vector3f pos, Vector3f color, Vector3f atten) : position(pos), diffuseColor(color), attenuation(atten){};
public:
    inline void setPosition(float x, float y, float z){position.set(x, y, z); };
    inline void setPosition(Vector3f pos){position = pos; };

    inline Vector3f getSpecularColor(void) const{return specularColor; };
    inline Vector3f getAttenuation(void) const{return attenuation; };
    inline Vector3f getPosition(void) const{return position; };
    inline Vector3f getDiffuseColor(void)const{return diffuseColor; };

    inline static PointerPointLight create(Vector3f position, Vector3f color){
        return PointerPointLight(new PointLight(position, color));
    }

    inline static PointerPointLight create(Vector3f position, Vector3f color, Vector3f attenuation){
        return PointerPointLight(new PointLight(position, color, attenuation));
    }
    virtual inline LightData getData(void) const{
        return {LightTypes::POINT, getPosition().getVec(), getDiffuseColor().getVec(), getSpecularColor().getVec(), getAttenuation().getVec(), {0, 0, 0}, 0, 0};
    }
};



#endif //GRAPHICSPROJECT_LIGHT_H
