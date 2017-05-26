//
// Created by gabriel on 10.10.2016.
//

#ifndef GRAPHICSPROJECT_LIGHT_H
#define GRAPHICSPROJECT_LIGHT_H


#include "src/utils/math/objects/Vectors.h"

class PointLight {
    Vector3f _position;
    Vector3f _diffuseColor;
    Vector3f _specularColor  = Vector3f(0.5f, 0.5f, 0.5f);
    Vector3f _attenuation    = Vector3f(1, 0, 0);
protected:
    inline PointLight(const Vector3f& position,
                      const Vector3f& color,
                      const Vector3f& attenuation = Vector3f(1, 0, 0)) :
            _position(position),
            _diffuseColor(color),
            _attenuation(attenuation){};
public:
    inline void setPosition(const float x, const float y, const float z){_position.set(x, y, z); };
    inline void setPosition(const Vector3f& pos){_position = pos; };

    inline Vector3f getSpecularColor(void) const{return _specularColor; };
    inline Vector3f getDiffuseColor(void)const{return _diffuseColor; };
    inline Vector3f getAttenuation(void) const{return _attenuation; };
    inline Vector3f getPosition(void) const{return _position; };

    inline static PointerPointLight create(const Vector3f& position, const Vector3f& color){
        return PointerPointLight(new PointLight(position, color));
    }

    inline static PointerPointLight create(const Vector3f& position, const Vector3f& color, const Vector3f& attenuation){
        return PointerPointLight(new PointLight(position, color, attenuation));
    }
    virtual inline LightData getData(void) const{
        return {LightTypes::POINT,
                _position.getVec(),
                _diffuseColor.getVec(),
                _specularColor.getVec(),
                _attenuation.getVec(),
                {0, 0, 0},
                0,
                0};
    }
};



#endif //GRAPHICSPROJECT_LIGHT_H
