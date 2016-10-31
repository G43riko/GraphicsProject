//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_ENTITY_H
#define GRAPHICSPROJECT_ENTITY_H


#include "../../utils/Vectors.h"
#include "MaterialedModel.h"
#include "Transform.h"
#include "../../utils/utils.h"

class Entity {
    private:
        int id;
        PointerMaterialedModel model;
        Transform transform = Transform();

    public:
        Entity(PointerMaterialedModel, const Vector3f &, const Vector3f &, const Vector3f &);
        int getId(void);

        void move(float, float, float);
        void rotate(float, float, float);

        PointerMaterialedModel getModel(void);
        Transform * getTransform(void);
};
typedef std::shared_ptr<Entity> PointerEntity;

PointerEntity createEntity(PointerMaterialedModel, const Vector3f &, const Vector3f &, const Vector3f &);

#endif //GRAPHICSPROJECT_ENTITY_H
