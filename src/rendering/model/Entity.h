//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_ENTITY_H
#define GRAPHICSPROJECT_ENTITY_H


#include "../../utils/Vectors.h"
#include "MaterialedModel.h"
#include "Transform.h"
#include "../../utils/utils.h"

class Entity;
typedef std::shared_ptr<Entity> PointerEntity;
class Entity {
    private:
        int id;
        PointerMaterialedModel model;
        Transform transform = Transform();

    public:
        Entity(PointerMaterialedModel, PointerVector3f, PointerVector3f, PointerVector3f);
        int getId(void);
        void move(float, float, float);

        void rotate(float, float, float);
        PointerMaterialedModel getModel(void);
        Transform * getTransform(void);
        static PointerEntity create(PointerMaterialedModel model, PointerVector3f pos, PointerVector3f rot, PointerVector3f scale){
            return PointerEntity(new Entity(model, pos, rot, scale));
        }
};



#endif //GRAPHICSPROJECT_ENTITY_H
