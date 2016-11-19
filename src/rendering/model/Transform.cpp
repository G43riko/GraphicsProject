//
// Created by gabriel on 25.9.2016.
//

#include "Transform.h"


Transform::Transform(Vector3f position, Vector3f rotation, Vector3f scale) {
    init(position, rotation, scale);
}
void Transform::init(const Vector3f &position, const Vector3f &rotation, const Vector3f &scale) {
    this -> position = position;
    this -> rotation.rotate(rotation);
    this -> scale = scale;
}
void Transform::move(float x, float y, float z){
    position.x += x;
    position.y += y;
    position.z += z;
}

Matrix4f Transform::getTransformation(void){
    Matrix4f translationMatrix = *Matrix4f::initTranslation(position.x, position.y, position.z);
    Matrix4f scaleMatrix = *Matrix4f::initScale(scale.x, scale.y, scale.z);
    return scaleMatrix * rotation.toRotationMatrix() * translationMatrix;
}
void Transform::setPosition(Vector3f vec){
    position = vec;
}

Vector3f * Transform::getPosition(void){return &position;}
float Transform::getPosX(void){return position.x;}
float Transform::getPosY(void){return position.y;}
float Transform::getPosZ(void){return position.z;}
Quaternion * Transform::getRotation(void){return &rotation;}

Vector3f * Transform::getScale(void){return &scale;}
float Transform::getScaleX(void){return scale.x;}
float Transform::getScaleY(void){return scale.y;}
float Transform::getScaleZ(void){return scale.z;}
