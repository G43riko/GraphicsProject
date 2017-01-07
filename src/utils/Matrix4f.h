//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_MATRIX4F_H
#define GRAPHICSPROJECT_MATRIX4F_H

#include "Vectors.h"
#include <iomanip>
#include <glm/mat4x4.hpp>

#define TO_DEGREES(X) X * 180 / M_PI
#define TO_RADIANS(X) X * M_PI / 180

class Matrix4f {
public:
    static int counter;
    static int minus;
    bool created = false;
    float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;
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

    static Matrix4f setIdentity(Matrix4f&);

    static Matrix4f mul(const Matrix4f &, Matrix4f, Matrix4f * = nullptr);
    static Vector4f transform(Matrix4f, Vector4f, Vector4f * = nullptr);
    static Matrix4f translate(Vector3f, Matrix4f, Matrix4f * = nullptr);
    static Matrix4f translate(Vector2f, Matrix4f, Matrix4f * = nullptr);
    static Matrix4f rotate(float, Vector3f, Matrix4f, Matrix4f * = nullptr);
    static Matrix4f scale(Vector3f, Matrix4f, Matrix4f *);

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
