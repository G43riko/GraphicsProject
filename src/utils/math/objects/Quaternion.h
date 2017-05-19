//
// Created by gabriel on 29.10.2016.
//

#ifndef GRAPHICSPROJECT_QUATERNION_H
#define GRAPHICSPROJECT_QUATERNION_H

#include "Matrix4f.h"

class Quaternion : public Vector4f{
public:
    inline Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : Vector4f(x, y, z, w){}

    inline Quaternion(const Vector4f v) : Vector4f(v.x, v.y, v.z, v.w) {}

    inline Quaternion(const Vector3f axis, const float angle) {
        float sinHalfAngle = sinf(angle / 2);
        float cosHalfAngle = cosf(angle / 2);

        x = axis.x * sinHalfAngle;
        y = axis.y * sinHalfAngle;
        z = axis.z * sinHalfAngle;
        w = cosHalfAngle;
    }

    inline Quaternion(const Matrix4f m) {
        float trace = m.m00 + m.m11 + m.m22;

        if(trace > 0) {
            float s = 0.5f / sqrtf(trace + 1.0f);
            w = 0.25f / s;
            x = (m.m12 - m.m21) * s;
            y = (m.m20 - m.m02) * s;
            z = (m.m01 - m.m10) * s;
        }
        else if(m.m00 > m.m11 && m.m00 > m.m22){
            float s = 2.0f * sqrtf(1.0f + m.m00 - m.m11 - m.m22);
            w = (m.m12 - m.m21) / s;
            x = 0.25f * s;
            y = (m.m10 + m.m01) / s;
            z = (m.m20 + m.m02) / s;
        }
        else if(m.m11 > m.m22){
            float s = 2.0f * sqrtf(1.0f + m.m11 - m.m00 - m.m22);
            w = (m.m20 - m.m02) / s;
            x = (m.m10 + m.m01) / s;
            y = 0.25f * s;
            z = (m.m21 + m.m12) / s;
        }
        else {
            float s = 2.0f * sqrtf(1.0f + m.m22 - m.m11 - m.m00);
            w = (m.m01 - m.m10) / s;
            x = (m.m20 + m.m02) / s;
            y = (m.m12 + m.m21) / s;
            z = 0.25f * s;
        }

        float len = length();
        w = w / len;
        x = x / len;
        y = y / len;
        z = z / len;
    }


    inline Quaternion operator * (const Quaternion& r) const{
        const float _w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
        const float _x = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
        const float _y = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
        const float _z = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);

        return Quaternion(_x, _y, _z, _w);
    }


    inline Quaternion operator *= (const Quaternion& r){
        *this = *this * r;
        return *this;
    }

    inline Quaternion operator * (const Vector3f& v) const{
        const float _w = - (x * v.x) - (y * v.y) - (z * v.z);
        const float _x =   (w * v.x) + (y * v.z) - (z * v.y);
        const float _y =   (w * v.y) + (z * v.x) - (x * v.z);
        const float _z =   (w * v.z) + (x * v.y) - (y * v.x);

        return Quaternion(_x, _y, _z, _w);
    }

    Matrix4f toRotationMatrix(void) const{
        Vector3f forward = Vector3f(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
        Vector3f up      = Vector3f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
        Vector3f right   = Vector3f(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
        return Matrix4f().InitRotationFromVectors(forward, up, right);
    }

    inline Vector3f getForward(void) const{return Vector3f(0, 0, 1).rotate(*this);}
    inline Vector3f getBack(void) const{return Vector3f(0, 0, -1).rotate(*this);}
    inline Vector3f getUp(void) const{return Vector3f(0, 1, 0).rotate(*this);}
    inline Vector3f getDown(void) const{return Vector3f(0, -1, 0).rotate(*this);}
    inline Vector3f getRight(void) const{return Vector3f(1, 0, 0).rotate(*this);}
    inline Vector3f getLeft(void) const{return Vector3f(-1, 0, 0).rotate(*this);}

    inline Quaternion conjugate(void) const{ return Quaternion(-x, -y, -z, w); }

    inline void rotate(const Vector3f & vec){
        Quaternion result = *this;
        if(NEQ(vec.x, 0)){
            result = result * Quaternion(Vector3f(1, 0, 0), vec.x);
        }
        if(NEQ(vec.y, 0)){
            result = result * Quaternion(Vector3f(0, 1, 0), vec.y);
        }
        if(NEQ(vec.z, 0)){
            result = result * Quaternion(Vector3f(0, 0, 1), vec.z);
        }

        x = result.x;
        y = result.y;
        z = result.z;
        w = result.w;
    }
    inline Quaternion mul(const Quaternion& r)  const{
        const float _w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
        const float _x = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
        const float _y = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
        const float _z = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);

        return Quaternion(_x, _y, _z, _w);
    }

    static Quaternion slerp(Quaternion qa, Quaternion qb, double t) {
        Quaternion qm = Quaternion();
        double cosHalfTheta = qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z;
        if (abs((int)cosHalfTheta) >= 1.0){
            qm.w = qa.w;
            qm.x = qa.x;
            qm.y = qa.y;
            qm.z = qa.z;
            return qm;
        }
        double halfTheta = acos(cosHalfTheta);
        double sinHalfTheta = sqrt(1.0 - cosHalfTheta * cosHalfTheta);
        if (fabs(sinHalfTheta) < 0.001){
            qm.w = (float)(qa.w * 0.5 + qb.w * 0.5);
            qm.x = (float)(qa.x * 0.5 + qb.x * 0.5);
            qm.y = (float)(qa.y * 0.5 + qb.y * 0.5);
            qm.z = (float)(qa.z * 0.5 + qb.z * 0.5);
            return qm;
        }
        double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
        double ratioB = sin(t * halfTheta) / sinHalfTheta;
        qm.w = (float)(qa.w * ratioA + qb.w * ratioB);
        qm.x = (float)(qa.x * ratioA + qb.x * ratioB);
        qm.y = (float)(qa.y * ratioA + qb.y * ratioB);
        qm.z = (float)(qa.z * ratioA + qb.z * ratioB);
        return qm;
    }

};


#endif //GRAPHICSPROJECT_QUATERNION_H
