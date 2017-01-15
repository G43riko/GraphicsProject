//
// Created by gabriel on 10.10.2016.
//

#include "PointLight.h"

PointerPointLight createPointLight(Vector3f position, Vector3f color){
    return PointerPointLight(new PointLight(position, color));
}

PointerPointLight createPointLight(Vector3f position, Vector3f color, Vector3f attenuation){
    return PointerPointLight(new PointLight(position, color, attenuation));
}