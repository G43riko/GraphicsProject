//
// Created by gabriel on 10.12.2016.
//

#ifndef GRAPHICSPROJECT_ENVIRONMENT_H
#define GRAPHICSPROJECT_ENVIRONMENT_H


#include <src/utils/Vectors.h>

class Environment {
    private:
        Vector3f gravity = Vector3f(0.0f, -0.01f, 0.0f);
        Vector3f wind = Vector3f(0.0f, 0.0f, 0.0f);
    public:
        Vector3f getAllForces(void){
            return gravity + wind;
        }
};


#endif //GRAPHICSPROJECT_ENVIRONMENT_H
