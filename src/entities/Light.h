//
// Created by gabriel on 10.10.2016.
//

#ifndef GRAPHICSPROJECT_LIGHT_H
#define GRAPHICSPROJECT_LIGHT_H


#include <src/utils/Vectors.h>
#include "../utils/utils.h"
class Light {
    public:
        Light(const Vector3f & position, const Vector3f & color, const Vector3f & attenuation){
            this -> attenuation = attenuation;
            this -> position = position;
            this -> color = color;
            id = IdGenerator::getId();
        }
        Light(const Vector3f & position, const Vector3f & color){
            this -> position = position;
            this -> color = color;
            id = IdGenerator::getId();
        }

        int getId(void){
            return id;
        }
        void setPosition(float x, float y, float z){
            position.x = x;
            position.y = y;
            position.z = z;
        }

        Vector3f getPosition(){
            return position;
        }
        Vector3f getColor(){
            return color;
        }
        Vector3f getAttenuation(){
            return attenuation;
        }

    private:
        Vector3f position = Vector3f(0, 0, 0);
        Vector3f color = Vector3f(1, 1, 1);
        Vector3f attenuation = Vector3f(1, 0, 0);
        int id;
};

typedef std::shared_ptr<Light> PointerLight;

PointerLight createLight(const Vector3f &, const Vector3f &);
PointerLight createLight(const Vector3f &, const Vector3f &, const Vector3f &);

#endif //GRAPHICSPROJECT_LIGHT_H
