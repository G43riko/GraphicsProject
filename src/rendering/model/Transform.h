//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_TRANSFORM_H
#define GRAPHICSPROJECT_TRANSFORM_H

#include "../../utils/Quaternion.h"
class Transform {
private:
    Vector3f position;
    Quaternion rotation;
    Vector3f scale;
    Transform * parent = nullptr;
public:
    /*
    void init(Vector3f &position, Quaternion &rotation, Vector3f &scale) {
        this -> position.x = position.x;
        this -> position.y = position.y;
        this -> position.z = position.z;
        this -> rotation.x = rotation.x;
        this -> rotation.y = rotation.y;
        this -> rotation.z = rotation.z;
        this -> rotation.w = rotation.w;
        this -> scale.x = scale.x;
        this -> scale.y = scale.y;
        this -> scale.z = scale.z;
    }
    */

    void init(const Vector3f &position, const Vector3f &rotation, const Vector3f &scale) {
        this -> position.x = position.x;
        this -> position.y = position.y;
        this -> position.z = position.z;
        this -> rotation.rotate(rotation);
        this -> scale.x = scale.x;
        this -> scale.y = scale.y;
        this -> scale.z = scale.z;
    }
    Transform(){};
    Transform(Vector3f, Vector3f, Vector3f);

    void move(float, float, float);
    void rotate(float, float, float);

    Matrix4f getTransformation(){
        Matrix4f translationMatrix = *Matrix4f::initTranslation(position.x, position.y, position.z);
        Matrix4f scaleMatrix = *Matrix4f::initScale(scale.x, scale.y, scale.z);
        return scaleMatrix * rotation.toRotationMatrix() * translationMatrix;
    }

    Vector3f * getPosition(void);
    float getPosX(void);
    float getPosY(void);
    float getPosZ(void);
    Quaternion * getRotation(void);
    float getRotX(void);
    float getRotY(void);
    float getRotZ(void);
    Vector3f * getScale(void);
    float getScaleX(void);
    float getScaleY(void);
    float getScaleZ(void);

    void setParent(Transform *);
};
/*
class Transform {
    private:
        PointerVector3f position = nullptr;
        PointerVector3f rotation = nullptr;
        PointerVector3f scale = nullptr;
        Transform * parent = nullptr;
    public:
        void init(PointerVector3f position, PointerVector3f rotation, PointerVector3f scale) {
            this -> position = position;
            this -> rotation = rotation;
            this -> scale = scale;
        }
        Transform() : Transform(nullptr, nullptr, nullptr){};
        Transform(PointerVector3f, PointerVector3f, PointerVector3f);
        void move(float, float, float);

        void rotate(float, float, float);

        PointerVector3f getPosition(void);
        float getPosX(void);
        float getPosY(void);
        float getPosZ(void);
        PointerVector3f getRotation(void);
        float getRotX(void);
        float getRotY(void);
        float getRotZ(void);
        PointerVector3f getScale(void);
        float getScaleX(void);
        float getScaleY(void);
        float getScaleZ(void);

        void setParent(Transform *);
};
*/

#endif //GRAPHICSPROJECT_TRANSFORM_H
