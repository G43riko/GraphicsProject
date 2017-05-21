//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_MATRIX4F_H
#define GRAPHICSPROJECT_MATRIX4F_H

#include "Vectors.h"
#include <iomanip>
#include <glm/mat4x4.hpp>
#include <xmmintrin.h>

inline void M4x4_SSE(const float *A, const float *B, float *C) {
    __m128 row1 = _mm_load_ps(&B[0]);
    __m128 row2 = _mm_load_ps(&B[4]);
    __m128 row3 = _mm_load_ps(&B[8]);
    __m128 row4 = _mm_load_ps(&B[12]);
    for(int i=0; i<4; i++) {
        __m128 brod1 = _mm_set1_ps(A[4 * i + 0]);
        __m128 brod2 = _mm_set1_ps(A[4 * i + 1]);
        __m128 brod3 = _mm_set1_ps(A[4 * i + 2]);
        __m128 brod4 = _mm_set1_ps(A[4 * i + 3]);
        __m128 row = _mm_add_ps(
                _mm_add_ps(
                        _mm_mul_ps(brod1, row1),
                        _mm_mul_ps(brod2, row2)),
                _mm_add_ps(
                        _mm_mul_ps(brod3, row3),
                        _mm_mul_ps(brod4, row4)));
        _mm_store_ps(&C[4*i], row);
    }
}

class Matrix4f {
public:
    float m01 = 0, m02 = 0, m03 = 0, m10 = 0, m12 = 0, m13 = 0, m20 = 0, m21 = 0, m23 = 0, m30 = 0, m31 = 0, m32 = 0;
    float m00 = 1, m11 = 1, m22 = 1, m33 = 1;
    ~Matrix4f(){
        //Matrix4f::counter--;
        //std::cout << "nicim: " << Matrix4f::minus <<  (created ? " som " : " niesom ") << "\n";
    }
    Matrix4f(const float * mat){
        m00 = mat[0];
        m10 = mat[1];
        m20 = mat[2];
        m30 = mat[3];
        m01 = mat[4];
        m11 = mat[5];
        m21 = mat[6];
        m31 = mat[7];
        m02 = mat[8];
        m12 = mat[9];
        m22 = mat[10];
        m32 = mat[11];
        m03 = mat[12];
        m13 = mat[13];
        m23 = mat[14];
        m33 = mat[15];
    }
    Matrix4f(const glm::mat4 mat){
        m00 = mat[0][0];
        m10 = mat[0][1];
        m20 = mat[0][2];
        m30 = mat[0][3];
        m01 = mat[1][0];
        m11 = mat[1][1];
        m21 = mat[1][2];
        m31 = mat[1][3];
        m02 = mat[2][0];
        m12 = mat[2][1];
        m22 = mat[2][2];
        m32 = mat[2][3];
        m03 = mat[3][0];
        m13 = mat[3][1];
        m23 = mat[3][2];
        m33 = mat[3][3];
//        std::cout << "tvorim: " << Matrix4f::counter << "\n";
    };

    static glm::mat4 toGlmMatrix(Matrix4f mat){
        glm::mat4 res;
        res[0][0] = mat.m00;;
        res[0][1] = mat.m10;;
        res[0][2] = mat.m20;;
        res[0][3] = mat.m30;;
        res[1][0] = mat.m01;;
        res[1][1] = mat.m11;;
        res[1][2] = mat.m21;;
        res[1][3] = mat.m31;;
        res[2][0] = mat.m02;;
        res[2][1] = mat.m12;;
        res[2][2] = mat.m22;;
        res[2][3] = mat.m32;;
        res[3][0] = mat.m03;;
        res[3][1] = mat.m13;;
        res[3][2] = mat.m23;;
        res[3][3] = mat.m33;;
        return res;
    }
    static inline Matrix4f InitRotationEuler(const float x, const float y, const float z) {
        Matrix4f rx, ry, rz;

        rx.m00 = 1;   rx.m10 = 0  ;  rx.m20 = 0   ; rx.m30 = 0;
        rx.m01 = 0;   rx.m11 = COSF(x);  rx.m21 = -SINF(x); rx.m31 = 0;
        rx.m02 = 0;   rx.m12 = SINF(x);  rx.m22 = COSF(x) ; rx.m32 = 0;
        rx.m03 = 0;   rx.m13 = 0  ;  rx.m23 = 0   ; rx.m33 = 1;

        ry.m00 = COSF(y); ry.m10 = 0;    ry.m20 = -SINF(y); ry.m30 = 0;
        ry.m01 = 0  ; ry.m11 = 1;    ry.m21 = 0   ; ry.m31 = 0;
        ry.m02 = SINF(y); ry.m12 = 0;    ry.m22 = COSF(y) ; ry.m32 = 0;
        ry.m03 = 0  ; ry.m13 = 0;    ry.m23 = 0   ; ry.m33 = 1;

        rz.m00 = COSF(z); rz.m10 = -SINF(z); rz.m20 = 0;    rz.m30 = 0;
        rz.m01 = SINF(z); rz.m11 = COSF(z) ; rz.m21 = 0;    rz.m31 = 0;
        rz.m02 = 0  ; rz.m12 = 0   ; rz.m22 = 1;    rz.m32 = 0;
        rz.m03 = 0  ; rz.m13 = 0   ; rz.m23 = 0;    rz.m33 = 1;

        return rz * ry * rx;
    }

    inline Matrix4f(void){
//    std::cout << "tvorim: " << Matrix4f::counter << "\n";
    }

    static inline Matrix4f setIdentity(Matrix4f& m) {
        m.m01 = m.m02 = m.m03 = m.m10 = m.m12 = m.m13 = m.m20 = m.m21 = m.m23 = m.m30 = m.m31 = m.m32 = 0.0f;
        m.m00 = m.m11 = m.m22 = m.m33 = 1.0f;
        return m;
    }

    static inline Matrix4f mul(const Matrix4f & left, const Matrix4f right, Matrix4f * dest = nullptr) {
        /*
        float * a = new float[16]{left.m00, left.m10, left.m20, left.m30,
                                  left.m01, left.m11, left.m21, left.m31,
                                  left.m02, left.m12, left.m22, left.m32,
                                  left.m03, left.m13, left.m23, left.m33};

        float * b = new float[16]{right.m00, right.m10, right.m20, right.m30,
                                  right.m01, right.m11, right.m21, right.m31,
                                  right.m02, right.m12, right.m22, right.m32,
                                  right.m03, right.m13, right.m23, right.m33};
        */
        float * a = left.getArray();
        float * b = right.getArray();
        float * c = new float[16];
        M4x4_SSE(a, b, c);
        Matrix4f res = Matrix4f(c);
        delete[] a;
        delete[] b;
        delete[] c;
        /*
        Matrix4f res = Matrix4f();

        res.m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02 + left.m30 * right.m03;
        res.m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02 + left.m31 * right.m03;
        res.m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02 + left.m32 * right.m03;
        res.m03 = left.m03 * right.m00 + left.m13 * right.m01 + left.m23 * right.m02 + left.m33 * right.m03;
        res.m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12 + left.m30 * right.m13;
        res.m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12 + left.m31 * right.m13;
        res.m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12 + left.m32 * right.m13;
        res.m13 = left.m03 * right.m10 + left.m13 * right.m11 + left.m23 * right.m12 + left.m33 * right.m13;
        res.m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22 + left.m30 * right.m23;
        res.m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22 + left.m31 * right.m23;
        res.m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22 + left.m32 * right.m23;
        res.m23 = left.m03 * right.m20 + left.m13 * right.m21 + left.m23 * right.m22 + left.m33 * right.m23;
        res.m30 = left.m00 * right.m30 + left.m10 * right.m31 + left.m20 * right.m32 + left.m30 * right.m33;
        res.m31 = left.m01 * right.m30 + left.m11 * right.m31 + left.m21 * right.m32 + left.m31 * right.m33;
        res.m32 = left.m02 * right.m30 + left.m12 * right.m31 + left.m22 * right.m32 + left.m32 * right.m33;
        res.m33 = left.m03 * right.m30 + left.m13 * right.m31 + left.m23 * right.m32 + left.m33 * right.m33;
        */
        if (dest){
            *dest = res;
        }
        return res;
    }
    static inline Vector4f transform(const Matrix4f left, const Vector4f right, Vector4f * dest = nullptr) {
        Vector4f res = Vector4f(left.m00 * right.x + left.m10 * right.y + left.m20 * right.z + left.m30 * right.w,
                                left.m01 * right.x + left.m11 * right.y + left.m21 * right.z + left.m31 * right.w,
                                left.m02 * right.x + left.m12 * right.y + left.m22 * right.z + left.m32 * right.w,
                                left.m03 * right.x + left.m13 * right.y + left.m23 * right.z + left.m33 * right.w);

        if(dest){
            *dest = res;
        }
        return res;
    }
    static inline Matrix4f translate(const Vector3f vec, const Matrix4f src, Matrix4f * dest = nullptr) {
        Matrix4f res = Matrix4f();

        res.m30 += src.m00 * vec.x + src.m10 * vec.y + src.m20 * vec.z;
        res.m31 += src.m01 * vec.x + src.m11 * vec.y + src.m21 * vec.z;
        res.m32 += src.m02 * vec.x + src.m12 * vec.y + src.m22 * vec.z;
        res.m33 += src.m03 * vec.x + src.m13 * vec.y + src.m23 * vec.z;


        if (dest){
            *dest = res;
        }
        return res;
    }
/*

Matrix4f Matrix4f::translate(Vector2f vec, Matrix4f src, Matrix4f * dest) {
    Matrix4f res = Matrix4f();

    res.m30 += src.m00 * vec.x + src.m10 * vec.y;
    res.m31 += src.m01 * vec.x + src.m11 * vec.y;
    res.m32 += src.m02 * vec.x + src.m12 * vec.y;
    res.m33 += src.m03 * vec.x + src.m13 * vec.y;

    if (dest)
        *dest = res;
    return res;
}

 */
    static inline Matrix4f rotate(const float angle, const Vector3f axis, const Matrix4f src, Matrix4f * dest = nullptr) {
        Matrix4f res = Matrix4f();

        const float c = (float) cos(angle);
        const float s = (float) sin(angle);
        const float oneminusc = 1.0f - c;
        const float xy = axis.x * axis.y;
        const float yz = axis.y * axis.z;
        const float xz = axis.x * axis.z;
        const float xs = axis.x * s;
        const float ys = axis.y * s;
        const float zs = axis.z * s;

        const float f00 = axis.x * axis.x * oneminusc + c;
        const float f01 = xy * oneminusc + zs;
        const float f02 = xz * oneminusc - ys;
        // n[3] not used
        const float f10 = xy * oneminusc - zs;
        const float f11 = axis.y * axis.y * oneminusc + c;
        const float f12 = yz * oneminusc + xs;
        // n[7] not used
        const float f20 = xz * oneminusc + ys;
        const float f21 = yz * oneminusc - xs;
        const float f22 = axis.z * axis.z * oneminusc + c;

        const float t00 = src.m00 * f00 + src.m10 * f01 + src.m20 * f02;
        const float t01 = src.m01 * f00 + src.m11 * f01 + src.m21 * f02;
        const float t02 = src.m02 * f00 + src.m12 * f01 + src.m22 * f02;
        const float t03 = src.m03 * f00 + src.m13 * f01 + src.m23 * f02;
        const float t10 = src.m00 * f10 + src.m10 * f11 + src.m20 * f12;
        const float t11 = src.m01 * f10 + src.m11 * f11 + src.m21 * f12;
        const float t12 = src.m02 * f10 + src.m12 * f11 + src.m22 * f12;
        const float t13 = src.m03 * f10 + src.m13 * f11 + src.m23 * f12;
        res.m20 = src.m00 * f20 + src.m10 * f21 + src.m20 * f22;
        res.m21 = src.m01 * f20 + src.m11 * f21 + src.m21 * f22;
        res.m22 = src.m02 * f20 + src.m12 * f21 + src.m22 * f22;
        res.m23 = src.m03 * f20 + src.m13 * f21 + src.m23 * f22;
        res.m00 = t00;
        res.m01 = t01;
        res.m02 = t02;
        res.m03 = t03;
        res.m10 = t10;
        res.m11 = t11;
        res.m12 = t12;
        res.m13 = t13;

        if (dest){
            *dest = res;
        }
        return res;
    }

    static inline Matrix4f scale(const Vector3f vec, const Matrix4f src, Matrix4f * dest = nullptr) {
        Matrix4f res = Matrix4f();

        res.m00 = src.m00 * vec.x;
        res.m01 = src.m01 * vec.x;
        res.m02 = src.m02 * vec.x;
        res.m03 = src.m03 * vec.x;
        res.m10 = src.m10 * vec.y;
        res.m11 = src.m11 * vec.y;
        res.m12 = src.m12 * vec.y;
        res.m13 = src.m13 * vec.y;
        res.m20 = src.m20 * vec.z;
        res.m21 = src.m21 * vec.z;
        res.m22 = src.m22 * vec.z;
        res.m23 = src.m23 * vec.z;

        if (dest){
            *dest = res;
        }
        return res;
    }

    static inline Matrix4f initScale(const float x, const float y, const float z){
        Matrix4f result = Matrix4f();

        result.m00 = x;
        result.m11 = y;
        result.m22 = z;

        return result;
    }
    static inline Matrix4f initTranslation(const Vector3f& position){
        return initTranslation(position.x, position.y, position.z);
    }
    static inline Matrix4f initTranslation(const float x, const float y, const float z){
        Matrix4f result = Matrix4f();

        result.m03 = x;
        result.m13 = y;
        result.m23 = z;

        return result;
    }

    static inline Matrix4f initRotation(float x, float y, float z){
        Matrix4f rx = Matrix4f();
        Matrix4f ry = Matrix4f();
        Matrix4f rz = Matrix4f();

        x = TO_RADIANS(x);
        y = TO_RADIANS(y);
        z = TO_RADIANS(z);

        rx.m11 = rx.m22 = COSF(x);
        rx.m21 = SINF(x);
        rx.m12 = -rx.m21;

        ry.m00 = ry.m22 = COSF(y);
        ry.m20 = SINF(y);
        ry.m02 = -ry.m20;

        rz.m00 = rz.m11 = COSF(z);
        rz.m10 = SINF(z);
        rz.m01 = -rz.m10;

        return mul(rz, mul(ry, rx));
    }

    static inline Matrix4f initPerspective(const float fov, const float aspectRatio, const float zNear, const float zFar){
        float tanHalfFOV = static_cast<float>(tan(fov / 2));
        float zRange = zNear - zFar;
        Matrix4f result = Matrix4f();
//        result.m00 = 0;  result.m01 = 0;  result.m02 = 0;  result.m03 = 0;
//        result.m10 = 0;  result.m11 = 0;  result.m12 = 0;  result.m13 = 0;
//        result.m20 = 0;  result.m21 = 0;  result.m22 = 0;  result.m23 = 0;
//        result.m30 = 0;  result.m31 = 0;  result.m32 = 0;  result.m33 = 0;
        result.m00 = result.m11 = result.m22 = result.m33 = 0;

        result.m00 = 1.0f / (tanHalfFOV * aspectRatio);
        result.m11 = 1.0f / tanHalfFOV;
        result.m22 = -(zNear + zFar) / zRange;
        result.m32 = 1;
        result.m23 = 2 * zFar * zNear / zRange;

        return result;
    }

    static inline Matrix4f initOrthographic(const float left, const float right, const float bottom, const float top, const float near, const float far){
        float width = right - left;
        float height = top - bottom;
        float depth = far - near;

        Matrix4f result = Matrix4f();
        result.m00 = 2 / width;  result.m01 = 0;          result.m02 = 0;          result.m03 = -(right + left) / width;
        result.m10 = 0;          result.m11 = 2 / height; result.m12 = 0;          result.m13 = -(top + bottom) / height;
        result.m20 = 0;          result.m21 = 0;          result.m22 = -2 / depth; result.m23 = -(far + near) / depth;
        result.m30 = 0;          result.m31 = 0;          result.m32 = 0;          result.m33 = 1;

        return result;
    }

    inline Matrix4f InitRotationFromVectors(const Vector3f &n, const Vector3f &v, const Vector3f &u){
        m00 = u.x;  m10 = u.y;  m20 = u.z;  m30 = 0;
        m01 = v.x;  m11 = v.y;  m21 = v.z;  m31 = 0;
        m02 = n.x;  m12 = n.y;  m22 = n.z;  m32 = 0;
        m03 = 0;    m13 = 0;    m23 = 0;    m33 = 1;

        return *this;
    }

    Matrix4f operator * (const Matrix4f& matrix) const{
        return mul(*this, matrix);
    }
    Matrix4f operator *= (const Matrix4f& matrix){
        return mul(*this, matrix, this);
    }
    void show(const bool formate = true) const{
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "mat4x4((" << m00 << ", " << m10 << ", " << m20 << ", " << m30 << ")";
        if(formate)
            std::cout << std::endl;
        else
            std ::cout << ", ";
        std::cout << "(" << m01 << ", " << m11 << ", " << m21 << ", " << m31 << ")";

        if(formate)
            std::cout << std::endl;
        else
            std ::cout << ", ";
        std::cout << "(" << m02 << ", " << m12 << ", " << m22 << ", " << m32 << ")";
        if(formate)
            std::cout << std::endl;
        else
            std ::cout << ", ";
        std::cout << "(" << m03 << ", " << m13 << ", " << m23 << ", " << m33 << ")";
        std::cout << std::endl;
    }
    float * getArray(void) const{
        //float *f =
        //TODO toto dealokovať
        return new float[16]{m00, m10, m20, m30,m01, m11, m21, m31,m02, m12, m22, m32,m03, m13, m23, m33};
    }
};


#endif //GRAPHICSPROJECT_MATRIX4F_H
