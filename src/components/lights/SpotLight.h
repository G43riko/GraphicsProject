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
    inline SpotLight(Vector3f pos, Vector3f col, Vector3f att, Vector3f dir, float cutOff, float outerCutOff) :
            PointLight(pos, col, att),
            direction(dir),
            cutOff(cutOff),
            outerCutOff(outerCutOff){
    };
    inline float getCutOff(void) const{return cutOff; };
    inline float getOuterCutOff(void) const{return outerCutOff; };
    inline Vector3f getDirection(void) const{return direction; };
};

typedef std::shared_ptr<SpotLight> PointerSpotLight;

inline PointerSpotLight createSpotLight(Vector3f pos, Vector3f col, Vector3f att, Vector3f dir, float cutOff, float outerCutOff){
    return PointerSpotLight(new SpotLight(pos, col, att, dir, cutOff, outerCutOff));
}

#endif //GRAPHICSPROJECT_SPOTLIGHT_H
