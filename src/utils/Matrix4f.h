//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_MATRIX4F_H
#define GRAPHICSPROJECT_MATRIX4F_H

#include "Vectors.h"
#include <iomanip>
#include <glm/mat4x4.hpp>


class Matrix4f {
public:
    static int counter;
    static int minus;
    bool created = false;
    float m01 = 0, m02 = 0, m03 = 0, m10 = 0, m12 = 0, m13 = 0, m20 = 0, m21 = 0, m23 = 0, m30 = 0, m31 = 0, m32 = 0;
    float m00 = 1, m11 = 1, m22 = 1, m33 = 1;
    ~Matrix4f(){
        //Matrix4f::counter--;
        Matrix4f::minus++;
        //std::cout << "nicim: " << Matrix4f::minus <<  (created ? " som " : " niesom ") << "\n";
    }
    Matrix4f(void);
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
        Matrix4f::counter++;
        created = true;
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
    static Matrix4f InitRotationEuler(float x, float y, float z) {
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

    static Matrix4f setIdentity(Matrix4f&);

    static Matrix4f mul(const Matrix4f &, Matrix4f, Matrix4f * = nullptr);
    static Vector4f transform(Matrix4f, Vector4f, Vector4f * = nullptr);
    static Matrix4f translate(Vector3f, Matrix4f, Matrix4f * = nullptr);
    /*
    static Matrix4f translate(Vector2f, Matrix4f, Matrix4f * = nullptr);
    */
    static Matrix4f rotate(float, const Vector3f, const Matrix4f, Matrix4f * = nullptr);
    static Matrix4f scale(Vector3f, const Matrix4f, Matrix4f *);
    static Matrix4f initScale(float, float, float);
    static Matrix4f initTranslation(float, float, float);
    static Matrix4f initRotation(float, float, float);
    static Matrix4f initPerspective(float, float, float, float);
    static Matrix4f initOrthographic(float, float, float, float, float, float);

    Matrix4f InitRotationFromVectors(Vector3f &, Vector3f&, Vector3f&);

    Matrix4f operator * (const Matrix4f& matrix){
        return mul(*this, matrix);
    }
    Matrix4f operator *= (const Matrix4f& matrix){
        return mul(*this, matrix, this);
    }
    void show(bool formate = true){
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

    float * getArray() const{
        //float *f = new float[16]{m00, m01, m02, m03,m10, m11, m12, m13,m20, m21, m22, m23,m30, m31, m32, m33};
        //TODO toto dealokovať
        float *f = new float[16]{m00, m10, m20, m30,m01, m11, m21, m31,m02, m12, m22, m32,m03, m13, m23, m33};
        return f;
    }
};


#endif //GRAPHICSPROJECT_MATRIX4F_H
