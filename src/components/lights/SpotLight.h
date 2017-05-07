//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_SPOTLIGHT_H
#define GRAPHICSPROJECT_SPOTLIGHT_H


#include "PointLight.h"

class SpotLight : public PointLight{
private:
    Vector3f direction;
    float cutOff;
    float outerCutOff;
    inline SpotLight(Vector3f pos, Vector3f col, Vector3f att, Vector3f dir, float cutOff, float outerCutOff) :
            PointLight(pos, col, att),
            direction(dir),
            cutOff(cutOff),
            outerCutOff(outerCutOff){
    };
public:
    inline float getCutOff(void) const{return cutOff; };
    inline float getOuterCutOff(void) const{return outerCutOff; };
    inline Vector3f getDirection(void) const{return direction; };
    inline void setDirection(Vector3f dir){direction = dir;}


    inline static PointerSpotLight create(Vector3f pos, Vector3f col, Vector3f att, Vector3f dir, float cutOff, float outerCutOff){
        return PointerSpotLight(new SpotLight(pos, col, att, dir, cutOff, outerCutOff));
    }

    inline LightData getData(void) const{
        return {LightTypes::SPOT, getPosition().getVec(), getDiffuseColor().getVec(), getSpecularColor().getVec(), getAttenuation().getVec(), direction.getVec(), cutOff, outerCutOff};
    }
};




#endif //GRAPHICSPROJECT_SPOTLIGHT_H
