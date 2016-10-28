//
// Created by gabriel on 24.9.2016.
//

#include "Entity.h"

PointerEntity createEntity(PointerMaterialedModel model, PointerVector3f pos, PointerVector3f rot, PointerVector3f scale){
    return PointerEntity(new Entity(model, pos, rot, scale));
}

Entity::Entity(PointerMaterialedModel model, PointerVector3f position, PointerVector3f rotation, PointerVector3f scale) {
    this -> model = model;
    id = IdGenerator::getId();
    transform.init(*position, *rotation, *scale);
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
