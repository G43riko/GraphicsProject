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

Matrix4f Transform::getTransformation(bool pos, bool rot, bool sca) {
    Matrix4f result;
    Matrix4f::setIdentity(result);
    if (parent) {
        result = parent -> getTransformation(parentAttributes.x > 0, parentAttributes.y > 0, parentAttributes.z > 0) *
                 result;
    }
    if (pos){
        result = Matrix4f::initTranslation(position.x, position.y, position.z) * result;
    }
    if (rot){
        result = rotation.toRotationMatrix() * result;
    }
    if(sca){
        result = Matrix4f::initScale(scale.x, scale.y, scale.z) * result;
    }
    return result;
}
void Transform::setPosition(Vector3f vec){
    position = vec;
}
void Transform::setParent(Transform * parent, bool pos, bool rot, bool scale){
    this -> parent = parent;
    parentAttributes.x = pos ? 1 : 0;
    parentAttributes.y = rot ? 1 : 0;
    parentAttributes.z = scale ? 1 : 0;
}

Matrix4f Transform::getAverageTransformation(Transform a, Transform b, float ratio){
    Vector3f pos = linearInterpolation(*a.getPosition(), *b.getPosition(), ratio);
    //Quaternion rot = Quaternion::slerp(*a.getRotation(), *b.getRotation(), ratio); //linearInterpolation(*a.getRotation(), *b.getRotation(), ratio);
    Vector3f scale = linearInterpolation(*a.getScale(), *b.getScale(), ratio);
    return Transform(pos, a.getRotation() -> getForward(), scale).getTransformation(true, false, true);
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
