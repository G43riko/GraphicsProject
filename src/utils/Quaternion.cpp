//
// Created by gabriel on 29.10.2016.
//

#include "Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w){
    this -> x = x;
    this -> y = y;
    this -> z = z;
    this -> w = w;
}

Quaternion::Quaternion(Vector4f v) {
    this -> x = v.x;
    this -> y = v.y;
    this -> z = v.z;
    this -> w = v.w;
}

Quaternion::Quaternion(Vector3f axis, float angle) {
    float sinHalfAngle = sinf(angle / 2);
    float cosHalfAngle = cosf(angle / 2);

    x = axis.x * sinHalfAngle;
    y = axis.y * sinHalfAngle;
    y = axis.x * sinHalfAngle;
    w = cosHalfAngle;
}

Quaternion::Quaternion(Matrix4f m) {
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

Matrix4f Quaternion::toRotationMatrix() {
    Vector3f forward = Vector3f(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
    Vector3f up      = Vector3f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
    Vector3f right   = Vector3f(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));

    return Matrix4f().InitRotationFromVectors(forward, up, right);
}

Vector3f Quaternion::getForward(){return Vector3f(0, 0, 1).rotate(*this);}
Vector3f Quaternion::getBack() {return Vector3f(0, 0, -1).rotate(*this);}
Vector3f Quaternion::getUp(){return Vector3f(0, 1, 0).rotate(*this);}
Vector3f Quaternion::getDown(){return Vector3f(0, -1, 0).rotate(*this);}
Vector3f Quaternion::getRight(){return Vector3f(1, 0, 0).rotate(*this);}
Vector3f Quaternion::getLeft() {return Vector3f(-1, 0, 0).rotate(*this);}

Quaternion Quaternion::conjugate(){ return Quaternion(-x, -y, -z, w); }

Quaternion Quaternion::operator * (const Quaternion& r){
    const float _w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
    const float _x = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
    const float _y = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
    const float _z = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);

    return Quaternion(_x, _y, _z, _w);
}

Quaternion Quaternion::operator * (const Vector3f& v){
    const float _w = - (x * v.x) - (y * v.y) - (z * v.z);
    const float _x =   (w * v.x) + (y * v.z) - (z * v.y);
    const float _y =   (w * v.y) + (z * v.x) - (x * v.z);
    const float _z =   (w * v.z) + (x * v.y) - (y * v.x);

    return Quaternion(_x, _y, _z, _w);
}