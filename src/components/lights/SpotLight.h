//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_SPOTLIGHT_H
#define GRAPHICSPROJECT_SPOTLIGHT_H


#include "PointLight.h"

class SpotLight : public PointLight{
    Vector3f _direction;
    float _cutOff;
    float _outerCutOff;
    inline SpotLight(const Vector3f& position,
                     const Vector3f& diffuseColor,
                     const Vector3f& attenuation,
                     const Vector3f& direction,
                     const float cutOff,
                     const float outerCutOff) :
            PointLight(position, diffuseColor, attenuation),
            _direction(direction),
            _cutOff(cutOff),
            _outerCutOff(outerCutOff){
    };
public:
    inline float getCutOff(void) const{return _cutOff; };
    inline float getOuterCutOff(void) const{return _outerCutOff; };
    inline Vector3f getDirection(void) const{return _direction; };

    inline void setDirection(Vector3f dir){_direction = dir;}


    inline static PointerSpotLight create(const Vector3f& position,
                                          const Vector3f& diffuseColor,
                                          const Vector3f& attenuation,
                                          const Vector3f& direction,
                                          float cutOff,
                                          float outerCutOff){
        return PointerSpotLight(new SpotLight(position,
                                              diffuseColor,
                                              attenuation,
                                              direction,
                                              cutOff,
                                              outerCutOff));
    }

    inline LightData getData(void) const{
        return {LightTypes::SPOT,
                getPosition().getVec(),
                getDiffuseColor().getVec(),
                getSpecularColor().getVec(),
                getAttenuation().getVec(),
                _direction.getVec(),
                _cutOff,
                _outerCutOff};
    }
};




#endif //GRAPHICSPROJECT_SPOTLIGHT_H
