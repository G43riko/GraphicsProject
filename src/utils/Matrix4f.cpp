//
// Created by gabriel on 16.10.2016.
//

#include "Matrix4f.h"

Matrix4f::Matrix4f(){
    setIdentity(*this);
}

Matrix4f Matrix4f::setIdentity(Matrix4f& m) {
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

Matrix4f * Matrix4f::mul(Matrix4f left, Matrix4f right, Matrix4f * dest) {
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

Vector4f * Matrix4f::transform(Matrix4f left, Vector4f right, Vector4f * dest) {
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

Matrix4f * Matrix4f::translate(Vector3f vec, Matrix4f src, Matrix4f * dest) {
    if (!dest)
        dest = new Matrix4f();

    dest -> m30 += src.m00 * vec.x + src.m10 * vec.y + src.m20 * vec.z;
    dest -> m31 += src.m01 * vec.x + src.m11 * vec.y + src.m21 * vec.z;
    dest -> m32 += src.m02 * vec.x + src.m12 * vec.y + src.m22 * vec.z;
    dest -> m33 += src.m03 * vec.x + src.m13 * vec.y + src.m23 * vec.z;

    return dest;
}

Matrix4f * Matrix4f::translate(Vector2f vec, Matrix4f src, Matrix4f * dest) {
    if (!dest)
        dest = new Matrix4f();

    dest -> m30 += src.m00 * vec.x + src.m10 * vec.y;
    dest -> m31 += src.m01 * vec.x + src.m11 * vec.y;
    dest -> m32 += src.m02 * vec.x + src.m12 * vec.y;
    dest -> m33 += src.m03 * vec.x + src.m13 * vec.y;

    return dest;
}

Matrix4f * Matrix4f::rotate(float angle, Vector3f axis, Matrix4f * src, Matrix4f * dest) {
    if (!dest)
        dest = new Matrix4f();
    float c = (float) cos(angle);
    float s = (float) sin(angle);
    float oneminusc = 1.0f - c;
    float xy = axis.x*axis.y;
    float yz = axis.y*axis.z;
    float xz = axis.x*axis.z;
    float xs = axis.x*s;
    float ys = axis.y*s;
    float zs = axis.z*s;

    float f00 = axis.x*axis.x*oneminusc+c;
    float f01 = xy*oneminusc+zs;
    float f02 = xz*oneminusc-ys;
    // n[3] not used
    float f10 = xy*oneminusc-zs;
    float f11 = axis.y*axis.y*oneminusc+c;
    float f12 = yz*oneminusc+xs;
    // n[7] not used
    float f20 = xz*oneminusc+ys;
    float f21 = yz*oneminusc-xs;
    float f22 = axis.z*axis.z*oneminusc+c;

    float t00 = src -> m00 * f00 + src -> m10 * f01 + src -> m20 * f02;
    float t01 = src -> m01 * f00 + src -> m11 * f01 + src -> m21 * f02;
    float t02 = src -> m02 * f00 + src -> m12 * f01 + src -> m22 * f02;
    float t03 = src -> m03 * f00 + src -> m13 * f01 + src -> m23 * f02;
    float t10 = src -> m00 * f10 + src -> m10 * f11 + src -> m20 * f12;
    float t11 = src -> m01 * f10 + src -> m11 * f11 + src -> m21 * f12;
    float t12 = src -> m02 * f10 + src -> m12 * f11 + src -> m22 * f12;
    float t13 = src -> m03 * f10 + src -> m13 * f11 + src -> m23 * f12;
    dest -> m20 = src -> m00 * f20 + src -> m10 * f21 + src -> m20 * f22;
    dest -> m21 = src -> m01 * f20 + src -> m11 * f21 + src -> m21 * f22;
    dest -> m22 = src -> m02 * f20 + src -> m12 * f21 + src -> m22 * f22;
    dest -> m23 = src -> m03 * f20 + src -> m13 * f21 + src -> m23 * f22;
    dest -> m00 = t00;
    dest -> m01 = t01;
    dest -> m02 = t02;
    dest -> m03 = t03;
    dest -> m10 = t10;
    dest -> m11 = t11;
    dest -> m12 = t12;
    dest -> m13 = t13;
    return dest;
}

Matrix4f * Matrix4f::scale(Vector3f vec, Matrix4f src, Matrix4f * dest) {
    if (!dest)
        dest = new Matrix4f();
    dest -> m00 = src.m00 * vec.x;
    dest -> m01 = src.m01 * vec.x;
    dest -> m02 = src.m02 * vec.x;
    dest -> m03 = src.m03 * vec.x;
    dest -> m10 = src.m10 * vec.y;
    dest -> m11 = src.m11 * vec.y;
    dest -> m12 = src.m12 * vec.y;
    dest -> m13 = src.m13 * vec.y;
    dest -> m20 = src.m20 * vec.z;
    dest -> m21 = src.m21 * vec.z;
    dest -> m22 = src.m22 * vec.z;
    dest -> m23 = src.m23 * vec.z;
    return dest;
}

Matrix4f * Matrix4f::initScale(float x, float y, float z){
    Matrix4f * result = new Matrix4f();

    result -> m00 = x;    result -> m01 = 0;    result -> m02 = 0;    result -> m03 = 0;
    result -> m10 = 0;    result -> m11 = y;    result -> m12 = 0;    result -> m13 = 0;
    result -> m20 = 0;    result -> m21 = 0;    result -> m22 = z;    result -> m23 = 0;
    result -> m30 = 0;    result -> m31 = 0;    result -> m32 = 0;    result -> m33 = 1;

    return result;
}

Matrix4f * Matrix4f::initTranslation(float x, float y, float z){
    Matrix4f * result = new Matrix4f();

    result -> m00 = 1;    result -> m01 = 0;    result -> m02 = 0;    result -> m03 = x;
    result -> m10 = 0;    result -> m11 = 1;    result -> m12 = 0;    result -> m13 = y;
    result -> m20 = 0;    result -> m21 = 0;    result -> m22 = 1;    result -> m23 = z;
    result -> m30 = 0;    result -> m31 = 0;    result -> m32 = 0;    result -> m33 = 1;

    return result;
}

Matrix4f * Matrix4f::initRotation(float x, float y, float z){
    Matrix4f rx = Matrix4f();
    Matrix4f ry = Matrix4f();
    Matrix4f rz = Matrix4f();

    x = TO_RADIANS(x);
    y = TO_RADIANS(y);
    z = TO_RADIANS(z);

    rz.m00 = cos(z); rz.m01 = -sin(z);rz.m02 = 0;      rz.m03 = 0;
    rz.m10 = sin(z); rz.m11 = cos(z); rz.m12 = 0;      rz.m13 = 0;
    rz.m20 = 0;      rz.m21 = 0;      rz.m22 = 1;      rz.m23 = 0;
    rz.m30 = 0;      rz.m31 = 0;      rz.m32 = 0;      rz.m33 = 1;

    rx.m00 = 1;      rx.m01 = 0;      rx.m02 = 0;      rx.m03 = 0;
    rx.m10 = 0;      rx.m11 = cos(x); rx.m12 = -sin(x);rx.m13 = 0;
    rx.m20 = 0;      rx.m21 = sin(x); rx.m22 = cos(x); rx.m23 = 0;
    rx.m30 = 0;      rx.m31 = 0;      rx.m32 = 0;      rx.m33 = 1;

    ry.m00 = cos(y); ry.m01 = 0;      ry.m02 = -sin(y);ry.m03 = 0;
    ry.m10 = 0;      ry.m11 = 1;      ry.m12 = 0;      ry.m13 = 0;
    ry.m20 = sin(y); ry.m21 = 0;      ry.m22 = cos(y); ry.m23 = 0;
    ry.m30 = 0;      ry.m31 = 0;      ry.m32 = 0;      ry.m33 = 1;

    Matrix4f * result = mul(ry, rx);
    return mul(rz, *result, result);
}

Matrix4f * Matrix4f::initPerspective(float fov, float aspectRatio, float zNear, float zFar){
    float tanHalfFOV = static_cast<float>(tan(fov / 2));
    float zRange = zNear - zFar;
    Matrix4f * result = new Matrix4f();
    result -> m00 = 0;  result -> m01 = 0;  result -> m02 = 0;  result -> m03 = 0;
    result -> m10 = 0;  result -> m11 = 0;  result -> m12 = 0;  result -> m13 = 0;
    result -> m20 = 0;  result -> m21 = 0;  result -> m22 = 0;  result -> m23 = 0;
    result -> m30 = 0;  result -> m31 = 0;  result -> m32 = 0;  result -> m33 = 0;

    result -> m00 = 1.0f/(tanHalfFOV * aspectRatio);
    result -> m11 = 1.0f / tanHalfFOV;
    result -> m22 = -(zNear+zFar) / zRange;
    result -> m32 = 1;
    result -> m23 = 2 * zFar * zNear / zRange;

    return result;
}

Matrix4f * Matrix4f::initOrthographic(float left, float right, float bottom, float top, float near, float far){
    float width = right - left;
    float height = top - bottom;
    float depth = far - near;

    Matrix4f * result = new Matrix4f();
    result -> m00 = 2 / width;  result -> m01 = 0;          result -> m02 = 0;          result -> m03 = -(right + left) / width;
    result -> m10 = 0;          result -> m11 = 2 / height; result -> m12 = 0;          result -> m13 = -(top + bottom) / height;
    result -> m20 = 0;          result -> m21 = 0;          result -> m22 = -2 / depth; result -> m23 = -(far + near) / depth;
    result -> m30 = 0;          result -> m31 = 0;          result -> m32 = 0;          result -> m33 = 1;

    return result;
}

Matrix4f Matrix4f::InitRotationFromVectors(Vector3f &n, Vector3f &v, Vector3f &u){
    m00 = u.x;  m10 = u.y;  m20 = u.z;  m30 = 0;
    m01 = v.x;  m11 = v.y;  m21 = v.z;  m31 = 0;
    m02 = n.x;  m12 = n.y;  m22 = n.z;  m32 = 0;
    m03 = 0;    m13 = 0;    m23 = 0;    m33 = 1;

    return *this;
}