//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_ENTITY_H
#define GRAPHICSPROJECT_ENTITY_H


#include "../../utils/Vectors.h"
#include "MaterialedModel.h"
#include "src/utils/Transform.h"
#include "../../utils/utils.h"

class Entity {
private:
    bool alive                      = true;
    PointerMaterialedModel model    = nullptr;
    Transform transform             = Transform();
public:
    bool immortal = false;
    inline Entity(PointerMaterialedModel model, const Vector3f & position, const Vector3f & rotation, const Vector3f & scale) {
        this -> model = model;
        transform.init(position, rotation, scale);
        //transform = Transform(position, rotation, scale);
    }

    inline void move(float x, float y, float z){
        transform.move(x, y, z);
    }

    inline Transform * getTransform(void){return &transform; }
    inline PointerMaterialedModel getModel(void){return model; }
    inline bool isWireframe(void) const{return false; }
    inline void setAlive(bool value){ alive = immortal || value; }
    inline bool isAlive(void) const{return alive;}
};
typedef std::shared_ptr<Entity> PointerEntity;

inline PointerEntity createEntity(PointerMaterialedModel model, const Vector3f & pos, const Vector3f & rot, const Vector3f & scale){
    return PointerEntity(new Entity(model, pos, rot, scale));
}
#endif //GRAPHICSPROJECT_ENTITY_H
