//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_MATRIX4F_H
#define GRAPHICSPROJECT_MATRIX4F_H


#include "Vectors.h"

class Matrix4f {
public:
    float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;

    static Matrix4f setIdentity(Matrix4f m) {
        m.m00 = 1.0f;
        m.m01 = 0.0f;
        m.m02 = 0.0f;
        m.m03 = 0.0f;
        m.m10 = 0.0f;
        m.m11 = 1.0f;
        m.m12 = 0.0f;
        m.m13 = 0.0f;
        m.m20 = 0.0f;
        m.m21 = 0.0f;
        m.m22 = 1.0f;
        m.m23 = 0.0f;
        m.m30 = 0.0f;
        m.m31 = 0.0f;
        m.m32 = 0.0f;
        m.m33 = 1.0f;
        return m;
    }

    static Matrix4f * mul(Matrix4f left, Matrix4f right, Matrix4f * dest = nullptr) {
        if (!dest)
            dest = new Matrix4f();

        float m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02 + left.m30 * right.m03;
        float m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02 + left.m31 * right.m03;
        float m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02 + left.m32 * right.m03;
        float m03 = left.m03 * right.m00 + left.m13 * right.m01 + left.m23 * right.m02 + left.m33 * right.m03;
        float m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12 + left.m30 * right.m13;
        float m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12 + left.m31 * right.m13;
        float m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12 + left.m32 * right.m13;
        float m13 = left.m03 * right.m10 + left.m13 * right.m11 + left.m23 * right.m12 + left.m33 * right.m13;
        float m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22 + left.m30 * right.m23;
        float m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22 + left.m31 * right.m23;
        float m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22 + left.m32 * right.m23;
        float m23 = left.m03 * right.m20 + left.m13 * right.m21 + left.m23 * right.m22 + left.m33 * right.m23;
        float m30 = left.m00 * right.m30 + left.m10 * right.m31 + left.m20 * right.m32 + left.m30 * right.m33;
        float m31 = left.m01 * right.m30 + left.m11 * right.m31 + left.m21 * right.m32 + left.m31 * right.m33;
        float m32 = left.m02 * right.m30 + left.m12 * right.m31 + left.m22 * right.m32 + left.m32 * right.m33;
        float m33 = left.m03 * right.m30 + left.m13 * right.m31 + left.m23 * right.m32 + left.m33 * right.m33;

        dest -> m00 = m00;
        dest -> m01 = m01;
        dest -> m02 = m02;
        dest -> m03 = m03;
        dest -> m10 = m10;
        dest -> m11 = m11;
        dest -> m12 = m12;
        dest -> m13 = m13;
        dest -> m20 = m20;
        dest -> m21 = m21;
        dest -> m22 = m22;
        dest -> m23 = m23;
        dest -> m30 = m30;
        dest -> m31 = m31;
        dest -> m32 = m32;
        dest -> m33 = m33;

        return dest;
    }

    static Vector4f * transform(Matrix4f left, Vector4f right, Vector4f * dest = nullptr) {
        if (!dest)
            dest = new Vector4f();

        float x = left.m00 * right.x + left.m10 * right.y + left.m20 * right.z + left.m30 * right.w;
        float y = left.m01 * right.x + left.m11 * right.y + left.m21 * right.z + left.m31 * right.w;
        float z = left.m02 * right.x + left.m12 * right.y + left.m22 * right.z + left.m32 * right.w;
        float w = left.m03 * right.x + left.m13 * right.y + left.m23 * right.z + left.m33 * right.w;

        dest -> x = x;
        dest -> y = y;
        dest -> z = z;
        dest -> w = w;

        return dest;
    }

    static Matrix4f * translate(Vector3f vec, Matrix4f src, Matrix4f * dest = nullptr) {
        if (!dest)
            dest = new Matrix4f();

        dest -> m30 += src.m00 * vec.x + src.m10 * vec.y + src.m20 * vec.z;
        dest -> m31 += src.m01 * vec.x + src.m11 * vec.y + src.m21 * vec.z;
        dest -> m32 += src.m02 * vec.x + src.m12 * vec.y + src.m22 * vec.z;
        dest -> m33 += src.m03 * vec.x + src.m13 * vec.y + src.m23 * vec.z;

        return dest;
    }

    static Matrix4f * translate(Vector2f vec, Matrix4f src, Matrix4f * dest = nullptr) {
        if (!dest)
            dest = new Matrix4f();

        dest -> m30 += src.m00 * vec.x + src.m10 * vec.y;
        dest -> m31 += src.m01 * vec.x + src.m11 * vec.y;
        dest -> m32 += src.m02 * vec.x + src.m12 * vec.y;
        dest -> m33 += src.m03 * vec.x + src.m13 * vec.y;

        return dest;
    }

};


#endif //GRAPHICSPROJECT_MATRIX4F_H
