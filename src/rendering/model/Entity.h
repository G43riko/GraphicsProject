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
    PointerMaterialedModel model;
        Transform * transform;

    public:
        Entity(PointerMaterialedModel, PointerVector3f, PointerVector3f, PointerVector3f);

        void move(float, float, float);

        void rotate(float, float, float);
    PointerMaterialedModel getModel(void);
        Transform * getTransform(void);
};

typedef std::shared_ptr<Entity> PointerEntity;


#endif //GRAPHICSPROJECT_ENTITY_H
