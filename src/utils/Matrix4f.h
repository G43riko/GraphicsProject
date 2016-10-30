//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_MATRIX4F_H
#define GRAPHICSPROJECT_MATRIX4F_H

#include "Vectors.h"
#define TO_DEGREES(X) X * 180 / M_PI
#define TO_RADIANS(X) X * M_PI / 180

class Matrix4f {
public:
    float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;

    Matrix4f(void);

    static Matrix4f setIdentity(Matrix4f&);

    static Matrix4f * mul(Matrix4f, Matrix4f, Matrix4f * = nullptr);
    static Vector4f * transform(Matrix4f, Vector4f, Vector4f * = nullptr);
    static Matrix4f * translate(Vector3f, Matrix4f, Matrix4f * = nullptr);
    static Matrix4f * translate(Vector2f, Matrix4f, Matrix4f * = nullptr);
    static Matrix4f * rotate(float, Vector3f, Matrix4f *, Matrix4f * = nullptr);
    static Matrix4f * scale(Vector3f, Matrix4f, Matrix4f *);

    static Matrix4f * initScale(float, float, float);
    static Matrix4f * initTranslation(float, float, float);
    static Matrix4f * initRotation(float, float, float);
    static Matrix4f * initPerspective(float, float, float, float);
    static Matrix4f * initOrthographic(float, float, float, float, float, float);

    Matrix4f InitRotationFromVectors(Vector3f &, Vector3f&, Vector3f&);

    Matrix4f operator * (const Matrix4f& matrix){
        return *mul(*this, matrix);
    }
    Matrix4f operator *= (const Matrix4f& matrix){
        return *mul(*this, matrix, this);
    }
};


#endif //GRAPHICSPROJECT_MATRIX4F_H
