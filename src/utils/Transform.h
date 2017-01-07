//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_TRANSFORM_H
#define GRAPHICSPROJECT_TRANSFORM_H

#include "Quaternion.h"
#include "src/utils/Maths.h"

class Transform {
private:
    Vector3f position;
    Quaternion rotation;
    Vector3f scale;
    Vector3f parentAttributes = Vector3f(1, 1, 1);
    Transform * parent = nullptr;


public:
    void setRotation(Quaternion q){
        rotation = q;
    }
    void init(const Vector3f &, const Vector3f &, const Vector3f &);
    Transform(){};
    Transform(Vector3f, Vector3f, Vector3f);

    void move(const Vector3f & dir){
        move(dir.x, dir.y, dir.z);
    };
    void move(float, float, float);
    //void rotate(float, float, float);

    Matrix4f getTransformation(bool = true, bool = true, bool = true);
    void setPosition(Vector3f);
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

    void setParent(Transform *, bool = true, bool = true, bool = true);

    static Matrix4f getAverageTransformation(Transform a, Transform b, float ratio);
};

#endif //GRAPHICSPROJECT_TRANSFORM_H
