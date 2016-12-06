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

    static Quaternion slerp(Quaternion qa, Quaternion qb, double t) {
        Quaternion qm = Quaternion();
        double cosHalfTheta = qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z;
        if (abs(cosHalfTheta) >= 1.0){
            qm.w = qa.w;
            qm.x = qa.x;
            qm.y = qa.y;
            qm.z = qa.z;
            return qm;
        }
        double halfTheta = acos(cosHalfTheta);
        double sinHalfTheta = sqrt(1.0 - cosHalfTheta * cosHalfTheta);
        if (fabs(sinHalfTheta) < 0.001){
            qm.w = (qa.w * 0.5 + qb.w * 0.5);
            qm.x = (qa.x * 0.5 + qb.x * 0.5);
            qm.y = (qa.y * 0.5 + qb.y * 0.5);
            qm.z = (qa.z * 0.5 + qb.z * 0.5);
            return qm;
        }
        double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
        double ratioB = sin(t * halfTheta) / sinHalfTheta;
        qm.w = (qa.w * ratioA + qb.w * ratioB);
        qm.x = (qa.x * ratioA + qb.x * ratioB);
        qm.y = (qa.y * ratioA + qb.y * ratioB);
        qm.z = (qa.z * ratioA + qb.z * ratioB);
        return qm;
    }

};


#endif //GRAPHICSPROJECT_QUATERNION_H
