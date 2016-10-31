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
        void rotate(const Vector3f & vec){
            Quaternion result = *this;
            if(vec.x != 0)
                result = result * Quaternion(Vector3f(1, 0, 0), vec.x);

            if(vec.y != 0)
                result = result * Quaternion(Vector3f(0, 1, 0), vec.y);

            if(vec.z != 0)
                result = result * Quaternion(Vector3f(0, 0, 1), vec.z);

            x = result.x;
            y = result.y;
            z = result.z;
            w = result.w;
        }
        Quaternion operator * (const Quaternion&);
        Quaternion operator * (const Vector3f&);
};


#endif //GRAPHICSPROJECT_QUATERNION_H
