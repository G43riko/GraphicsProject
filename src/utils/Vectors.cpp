//
// Created by gabriel on 22.9.2016.
//
#include "Vectors.h"
#include <math.h>

Vector3f::Vector3f(float x, float y, float z) {
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

void Vector3f::show(void){
    std::cout << "[" << x << "x" << y << "x" << z << "]" << std::endl;
}

Vector3f * Vector3f::normalize(void){
    float length = (float)sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
    return this;
}

Vector3f * Vector3f::cross(Vector3f * v){
        float x_ = y * v -> z - z * v -> y;
        float y_ = z * v -> x - x * v -> z;
        float z_ = x * v -> y - y * v -> x;
        x = x_;
        y = y_;
        z = z_;
        return this;
}

Vector3f * Vector3f::getCross(Vector3f * v){
    float x_ = y * v -> z - z * v -> y;
    float y_ = z * v -> x - x * v -> z;
    float z_ = x * v -> y - y * v -> x;

    return new Vector3f(x_, y_, z_);
}

Vector3f * Vector3f::getNormal(void){
    Vector3f * result = new Vector3f(x, y, z);
    return result -> normalize();
}

Vector3f * Vector3f::mul(Vector3f * v){x *= v -> x; y *= v -> y; z *= v -> z; return this;};
Vector3f * Vector3f::mul(float v){x *= v; y *= v; z *= v; return this;};
Vector3f * Vector3f::getMul(Vector3f *v){new Vector3f(x / v -> x, y / v -> y, z / v -> z);};
Vector3f * Vector3f::getMul(float v){new Vector3f(x / v, y / v, z / v);};


Vector2f::Vector2f(float x, float y){
    this -> x = x;
    this -> y = y;
}