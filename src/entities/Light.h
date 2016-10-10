//
// Created by gabriel on 10.10.2016.
//

#ifndef GRAPHICSPROJECT_LIGHT_H
#define GRAPHICSPROJECT_LIGHT_H


#include <src/utils/Vectors.h>

class Light {
    public:
        Vector3f * position;
        Vector3f * color;

        Light(Vector3f * position, Vector3f * color){
            this -> position = position;
            this -> color = color;
        }
};


#endif //GRAPHICSPROJECT_LIGHT_H
