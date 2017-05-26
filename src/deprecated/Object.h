//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_OBJECT_H
#define GRAPHICSPROJECT_OBJECT_H


#include <src/utils/math/objects/Vectors.h>
#include <src/rendering/model/Entity.h>

class Object {
    PointerEntity object = nullptr;
    Vector3f velocity;
    Vector3f rotSpeed;
public:
    Object(PointerEntity object) : object(object){};
    virtual void update(float delta){};
};


#endif //GRAPHICSPROJECT_OBJECT_H
