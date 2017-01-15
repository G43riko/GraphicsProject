//
// Created by gabriel on 14.1.2017.
//

#include "SpotLight.h"

PointerSpotLight createSpotLight(Vector3f pos, Vector3f col, Vector3f att, Vector3f dir, float cutOff, float outerCutOff){
    return PointerSpotLight(new SpotLight(pos, col, att, dir, cutOff, outerCutOff));
}