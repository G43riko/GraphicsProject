//
// Created by gabriel on 10.10.2016.
//

#ifndef GRAPHICSPROJECT_LIGHT_H
#define GRAPHICSPROJECT_LIGHT_H


#include <src/utils/Vectors.h>
#include "../utils/utils.h"
class Light {
    public:
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

    private:
        PointerVector3f position;
        PointerVector3f color;
        int id;
};

typedef std::shared_ptr<Light> PointerLight;


#endif //GRAPHICSPROJECT_LIGHT_H
