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
    void init(const Vector3f &, const Vector3f &, const Vector3f &);
    Transform(){};
    Transform(Vector3f, Vector3f, Vector3f);

    void move(float, float, float);
    void rotate(float, float, float);

    Matrix4f getTransformation(void);
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

    void setParent(Transform *);
};

#endif //GRAPHICSPROJECT_TRANSFORM_H
