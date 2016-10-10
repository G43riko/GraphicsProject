//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_VECTORS_H
#define GRAPHICSPROJECT_VECTORS_H

#include <iostream>
#include <string.h>
#include <memory>

class Vector2f{
    public:
        float x, y;
        void show(bool = true);
        Vector2f(std::string data){
            std::string currentLine = strtok((char *)data.c_str(), " ");
            x = static_cast<float>(atof(currentLine.c_str()));
            currentLine = strtok(NULL, " ");
            y = static_cast<float>(atof(currentLine.c_str()));
        }

        Vector2f(float, float);
        Vector2f(void) : Vector2f(0.0f, 0.0f){};
        Vector2f(double x, double y) : Vector2f(static_cast<float>(x), static_cast<float>(y)){};
        Vector2f(int x, int y) : Vector2f(static_cast<float>(x), static_cast<float>(y)){};
        Vector2f(float);
        Vector2f(const Vector2f&);
};
class Vector3f{
    public:
        static int count;
        float x, y, z;
        ~Vector3f(void);
        Vector3f(void) : Vector3f(0.0f, 0.0f, 0.0f){};
        Vector3f(float, float, float);
        Vector3f(double x, double y, double z) : Vector3f(static_cast<float>(x),static_cast<float>(y), static_cast<float>(z)){};
        Vector3f(int x, int y, int z) : Vector3f(static_cast<float>(x),static_cast<float>(y), static_cast<float>(z)){};
        Vector3f(std::string);
        Vector3f(float);
        Vector3f(const Vector3f&);
        Vector3f * normalize(void);
        Vector3f * getNormal(void);
        Vector3f * cross(Vector3f *);
        Vector3f * getCross(Vector3f *);
        Vector3f * mul(Vector3f *);
        Vector3f * mul(float);
        Vector3f * getMul(Vector3f *);
        Vector3f * getMul(float);
        Vector3f * add(Vector3f *);
        float getLength(void);
        void show(bool = true);
};
typedef std::shared_ptr<Vector3f> PointerVector3f;

class Vector4f{
    public:
        float x, y, z, w;
        Vector4f(float, float, float, float);
        Vector4f(float);
        Vector4f(const Vector4f&);
};

class Matrix4f{
    public:
        float x, y, z;
};

template <typename T>class GVector{
    protected:
        T * data;
        int size;
    public:
        GVector(){};
        GVector(GVector<T> * arg){
            data = new T[arg -> size];
            size = arg -> size;
            for(int i=0 ; i<arg -> size ; i++)
                data[i] = arg -> data[i];

        }
        GVector<T> * mul(GVector<T> * arg){
            if(arg -> size != size)
                exit(10);
            for(int i=0 ; i<size ; i++)
                data[i] *= arg -> data[i];
        };

        GVector<T> * mul(T arg){
            if(arg -> size != size)
                exit(10);
            for(int i=0 ; i<size ; i++)
                data[i] *= arg;
        };
        GVector<T> * getMul(GVector<T> * arg){
            return  (new GVector<T>(this)) -> mul(arg);
        };
        GVector<T> * getMul(float arg){
            return  (new GVector<T>(this)) -> mul(arg);
        };
        void show(){
            std::cout << "[" << data[0];
            for(int i=1 ; i<size ; i++)
                std::cout << ", " << data[i];
            std::cout << "]" << std::endl;
        }
};


#endif //GRAPHICSPROJECT_VECTORS_H
