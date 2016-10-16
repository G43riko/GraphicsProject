//
// Created by gabriel on 22.9.2016.
//
#include "Vectors.h"
#include <math.h>

int Vector3f::count = 0;
Vector3f::Vector3f(float x, float y, float z) {
    this -> x = x;
    this -> y = y;
    this -> z = z;
    Vector3f::count++;
}
Vector3f::Vector3f(std::string data){
    std::string currentLine = strtok((char *)data.c_str(), " ");
    x = static_cast<float>(atof(currentLine.c_str()));
    currentLine = strtok(NULL, " ");
    y = static_cast<float>(atof(currentLine.c_str()));
    currentLine = strtok(NULL, " ");
    z = static_cast<float>(atof(currentLine.c_str()));
}

float Vector3f::getLength(void){
    return (x * x + y * y + z * z) * (x * x + y * y + z * z);
}

Vector3f::~Vector3f(void){
    Vector3f::count--;
}

Vector3f * Vector3f::add(Vector3f * v){
    x += v -> x;
    y += v -> y;
    z += v -> z;
    return this;
}

void Vector3f::show(bool endLine){
    std::cout << "[" << x << "x" << y << "x" << z << "]";
    if(endLine)
        std::cout << std::endl;

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

Vector3f * Vector3f::mul(Vector3f * v){x *= v -> x; y *= v -> y; z *= v -> z; return this;}
Vector3f * Vector3f::mul(float v){x *= v; y *= v; z *= v; return this;}
Vector3f * Vector3f::getMul(Vector3f * v){return new Vector3f(x * v -> x, y * v -> y, z * v -> z);}
Vector3f * Vector3f::getMul(float v){return new Vector3f(x * v, y * v, z * v);}

Vector2f::Vector2f(float x, float y){
    this -> x = x;
    this -> y = y;
}
Vector2f * Vector2f::getSub(Vector2f * v){
    return new Vector2f(x - v -> x, y - v -> y);
}

Vector3f * Vector3f::getSub(Vector3f * v){
    return new Vector3f(x - v -> x, y - v -> y, z - v -> z);
}

void Vector2f::show(bool endLine){
    std::cout << "[" << x << "x" << y << "]";
    if(endLine)
        std::cout << std::endl;
}


template<typename T> class GVector3 : public GVector<T>{
public:
    template<typename S>
    GVector3(S x, S y, S z) : GVector3(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)){}
    GVector3(GVector3<T> * a) : GVector3(a -> getX(), a -> getY(), a -> getZ()) {};
    GVector3(T x, T y, T z){
        this -> size = 3;
        this -> data = new T[this -> size]{x, y, z};
    }

    T getX(){return this -> data[0];}
    T getY(){return this -> data[1];}
    T getZ(){return this -> data[2];}
};
