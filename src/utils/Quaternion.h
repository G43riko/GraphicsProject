//
// Created by gabriel on 29.10.2016.
//

#ifndef GRAPHICSPROJECT_QUATERNION_H
#define GRAPHICSPROJECT_QUATERNION_H

#include "Matrix4f.h"

class Quaternion : public Vector4f{
    public:
        Quaternion(float = 0.0f, float = 0.0f, float = 0.0f, float = 1.0f);
        Quaternion(Vector4f);
        Quaternion(Vector3f, float);
        Quaternion(Matrix4f);

        Matrix4f toRotationMatrix(void);

        Vector3f getForward(void);
        Vector3f getBack(void);
        Vector3f getUp(void);
        Vector3f getDown(void);
        Vector3f getRight(void);
        Vector3f getLeft(void);

        Quaternion conjugate(void);

        Quaternion operator * (const Quaternion&);
        Quaternion operator * (const Vector3f&);
};


#endif //GRAPHICSPROJECT_QUATERNION_H
