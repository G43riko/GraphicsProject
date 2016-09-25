//
// Created by gabriel on 24.9.2016.
//

#include "Entity.h"

Entity::Entity(MaterialedModel * model, Vector3f * position, Vector3f * rotation, Vector3f * scale) {
    this -> model = model;
    transform = new Transform(position, rotation, scale);
}

void Entity::move(float x, float y, float z){
    transform -> move(x, y, z);
}

void Entity::rotate(float x, float y, float z){
    transform -> rotate(x, y, z);
}

MaterialedModel * Entity::getModel(void){
    return model;
}
Transform * Entity::getTransform(void){
    return transform;
}
