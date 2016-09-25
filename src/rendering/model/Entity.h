//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_ENTITY_H
#define GRAPHICSPROJECT_ENTITY_H


#include "../../utils/Vectors.h"
#include "MaterialedModel.h"
#include "Transform.h"

class Entity {
    private:
        MaterialedModel * model;
        Transform * transform;

    public:
        Entity(MaterialedModel * model, Vector3f * position, Vector3f * rotation, Vector3f * scale) {
            this -> model = model;
            transform = new Transform(position, rotation, scale);
        }

        void move(float x, float y, float z){
            transform -> move(x, y, z);
        }

        void rotate(float x, float y, float z){
            transform -> rotate(x, y, z);
        }

        MaterialedModel * getModel(){
            return model;
        }
        Transform * getTransform(){
            return transform;
        }
};


#endif //GRAPHICSPROJECT_ENTITY_H
