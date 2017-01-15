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
public:
    SpotLight(Vector3f pos, Vector3f col, Vector3f att, Vector3f dir, float cutOff, float outerCutOff) :
            PointLight(pos, col, att),
            direction(dir),
            cutOff(cutOff),
            outerCutOff(outerCutOff){
    };
    float getCutOff(void){
        return cutOff;
    };
    float getOuterCutOff(void){
        return outerCutOff;
    };
    Vector3f getDirection(void){
        return direction;
    };
};

typedef std::shared_ptr<SpotLight> PointerSpotLight;

PointerSpotLight createSpotLight(Vector3f pos, Vector3f col, Vector3f att, Vector3f dir, float cutOff, float outerCutOff);


#endif //GRAPHICSPROJECT_SPOTLIGHT_H
