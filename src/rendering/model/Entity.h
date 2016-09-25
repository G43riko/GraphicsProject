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
        Entity(MaterialedModel *, Vector3f *, Vector3f *, Vector3f *);

        void move(float, float, float);

        void rotate(float, float, float);
        MaterialedModel * getModel(void);
        Transform * getTransform(void);
};


#endif //GRAPHICSPROJECT_ENTITY_H
