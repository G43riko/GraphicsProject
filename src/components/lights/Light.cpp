//
// Created by gabriel on 10.10.2016.
//

#include "Light.h"

PointerLight createLight(const Vector3f & position, const Vector3f & color){
    return PointerLight(new Light(position, color));
}

PointerLight createLight(const Vector3f & position, const Vector3f & color, const Vector3f & attenuation){
    return PointerLight(new Light(position, color, attenuation));
}