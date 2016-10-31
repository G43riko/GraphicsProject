//
// Created by gabriel on 10.10.2016.
//

#ifndef GRAPHICSPROJECT_LIGHT_H
#define GRAPHICSPROJECT_LIGHT_H


#include <src/utils/Vectors.h>
#include "../utils/utils.h"
class Light {
    public:
        Light(PointerVector3f position, PointerVector3f color, const Vector3f & attenuation){
            this -> attenuation = attenuation;
            this -> position = position;
            this -> color = color;
            id = IdGenerator::getId();
        }
        Light(PointerVector3f position, PointerVector3f color){
            this -> position = position;
            this -> color = color;
            id = IdGenerator::getId();
        }

        int getId(void){
            return id;
        }

        PointerVector3f getPosition(){
            return position;
        }
        PointerVector3f getColor(){
            return color;
        }
        Vector3f getAttenuation(){
            return attenuation;
        }

    private:
        PointerVector3f position;
        PointerVector3f color;
        Vector3f attenuation = (1, 0, 0);
        int id;
};

typedef std::shared_ptr<Light> PointerLight;

PointerLight createLight(PointerVector3f position, PointerVector3f color){
    return PointerLight(new Light(position, color));
}

PointerLight createLight(PointerVector3f position, PointerVector3f color, const Vector3f & attenuation){
    return PointerLight(new Light(position, color, attenuation));
}

#endif //GRAPHICSPROJECT_LIGHT_H
