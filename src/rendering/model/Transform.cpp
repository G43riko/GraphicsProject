//
// Created by gabriel on 25.9.2016.
//

#include "Transform.h"


Transform::Transform(Vector3f position, Vector3f rotation, Vector3f scale) {
    init(position, rotation, scale);
}

void Transform::move(float x, float y, float z){
    position.x += x;
    position.y += y;
    position.z += z;
}

void Transform::rotate(float x, float y, float z){
    rotation.x += x;
    rotation.y += y;
    rotation.z += z;
}

Vector3f * Transform::getPosition(void){return &position;}
float Transform::getPosX(void){return position.x;}
float Transform::getPosY(void){return position.y;}
float Transform::getPosZ(void){return position.z;}
Vector3f * Transform::getRotation(void){return &rotation;}
float Transform::getRotX(void){return rotation.x;}
float Transform::getRotY(void){return rotation.y;}
float Transform::getRotZ(void){return rotation.z;}
Vector3f * Transform::getScale(void){return &scale;}
float Transform::getScaleX(void){return scale.x;}
float Transform::getScaleY(void){return scale.y;}
float Transform::getScaleZ(void){return scale.z;}

