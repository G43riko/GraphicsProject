//
// Created by gabriel on 24.9.2016.
//

#include "Entity.h"

PointerEntity createEntity(PointerMaterialedModel model, const Vector3f & pos, const Vector3f & rot, const Vector3f & scale){
    return PointerEntity(new Entity(model, pos, rot, scale));
}

Entity::Entity(PointerMaterialedModel model, const Vector3f & position, const Vector3f & rotation, const Vector3f & scale) {
    this -> model = model;
    id = IdGenerator::getId();
    transform.init(position, rotation, scale);
    //transform = Transform(position, rotation, scale);
}

void Entity::move(float x, float y, float z){
    transform.move(x, y, z);
}

void Entity::rotate(float x, float y, float z){
    transform.rotate(x, y, z);
}

int Entity::getId(void){
    return id;
}

PointerMaterialedModel Entity::getModel(void){
    return model;
}
Transform * Entity::getTransform(void){
    return &transform;
}
