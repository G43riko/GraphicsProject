//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_VECTORS_H
#define GRAPHICSPROJECT_VECTORS_H

#include <iostream>
#include <string.h>
#include <memory>
#include <math.h>


class Vector3f;
typedef std::shared_ptr<Vector3f> PointerVector3f;
class Quaternion;

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
        Vector2f(float val) : Vector2f(val, val){};
        friend Vector2f operator * (const Vector2f &c1, const float& val){ return Vector2f(c1.x * val, c1.y * val); }
        friend Vector2f operator - (const Vector2f &c1, const Vector2f &c2){return Vector2f(c1.x - c2.x, c1.y - c2.y); }
        friend Vector2f operator + (const Vector2f &c1, const Vector2f &c2){return Vector2f(c1.x + c2.x, c1.y + c2.y); }
        Vector2f& operator = (const Vector2f& other){
            this -> x = other.x;
            this -> y = other.y;
            return *this;
        }

    int getXi(){ return static_cast<int>(x); }
    int getYi(){ return static_cast<int>(y); }
        //Vector2f(const Vector2f&);
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
        Vector3f(Vector3f* vec) : Vector3f(vec -> x, vec -> y, vec -> z){};
        Vector3f(float val) : Vector3f(val, val, val){};
        Vector3f(const Vector3f& vec) : Vector3f(vec.x, vec.y, vec.z){};
        Vector3f normalize(void);
        Vector3f getNormal(void);
        Vector3f cross(Vector3f *);
        Vector3f getCross(Vector3f *);

        Vector3f& operator *= (const float& val){ this -> x *= val, this -> y *= val, this -> z *= val;return *this; }
        Vector3f operator *= (const Vector3f& v){ this -> x *= v.x, this -> y *= v.y, this -> z *= v.z;return *this; }
        friend Vector3f operator * (const Vector3f &c1, const Vector3f &c2){ return Vector3f(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z); }
        friend Vector3f operator * (const Vector3f &c1, const float& val){ return Vector3f(c1.x * val, c1.y * val, c1.z * val); }

        Vector3f operator /= (const float& val){ this -> x /= val, this -> y /= val, this -> z /= val;return *this; }
        Vector3f operator /= (const Vector3f& v){ this -> x /= v.x, this -> y /= v.y, this -> z /= v.z;return *this; }
        friend Vector3f operator / (const Vector3f &c1, const Vector3f &c2){ return Vector3f(c1.x / c2.x, c1.y / c2.y, c1.z / c2.z); }
        friend Vector3f operator / (const Vector3f &c1, const float& val){ return Vector3f(c1.x / val, c1.y / val, c1.z / val); }

        Vector3f operator += (const float& val){ this -> x += val, this -> y += val, this -> z += val;return *this; }
        Vector3f operator += (const Vector3f& v){ this -> x += v.x, this -> y += v.y, this -> z += v.z;return *this; }
        friend Vector3f operator + (const Vector3f &c1, const Vector3f &c2){ return Vector3f(c1.x + c2.x, c1.y + c2.y, c1.z + c2.z); }
        friend Vector3f operator + (const Vector3f &c1, const float& val){ return Vector3f(c1.x + val, c1.y + val, c1.z + val); }

        Vector3f operator -= (const float& val){ this -> x -= val, this -> y -= val, this -> z -= val;return *this; }
        Vector3f operator -= (const Vector3f& v){ this -> x -= v.x, this -> y -= v.y, this -> z -= v.z;return *this; }
        friend Vector3f operator - (const Vector3f &c1, const Vector3f &c2){ return Vector3f(c1.x - c2.x, c1.y - c2.y, c1.z - c2.z); }
        friend Vector3f operator - (const Vector3f &c1, const float& val){ return Vector3f(c1.x - val, c1.y - val, c1.z - val); }

        Vector3f& operator = (const Vector3f& other){
            this -> x = other.x;
            this -> y = other.y;
            this -> z = other.z;
            return *this;
        }

        int getXi(){ return static_cast<int>(x); }
        int getYi(){ return static_cast<int>(y); }
        int getZi(){ return static_cast<int>(z); }

        template <typename T>
        T getXt(){return static_cast<T>(x); }
        template <typename T>
        T getYt(){return static_cast<T>(y); }
        template <typename T>
        T getZt(){return static_cast<T>(z); }

        unsigned char getXuc(){ return static_cast<unsigned char>(x); }
        unsigned char getYuc(){ return static_cast<unsigned char>(y); }
        unsigned char getZuc(){ return static_cast<unsigned char>(z); }

        Vector3f rotate(Quaternion);

        float getLength(void);
        void show(bool = true);

};



class Vector4f{
    public:
        float x, y, z, w;
        Vector4f(void) : Vector4f(0, 0, 0, 0){};
        Vector4f(float val) : x(val), y(val), z(val), w(val){};
        Vector4f(const Vector4f& v) : x(v.x), y(v.y), z(v.z), w(v.w){};
        Vector4f(float x, float y, float z, float w){
            this -> x = x;
            this -> y = y;
            this -> z = z;
            this -> w = w;
        };
        Vector4f normalize(void){
            float len = length();
            x /= len;
            y /= len;
            z /= len;
            w /= len;
            return *this;
        };

        Vector4f getNormal(void){
            float len = length();
            return Vector4f(x /= len, y /= len, z /= len, w /= len);
        };

        float lengthSquared() {
            return x * x + y * y + z * z + w * w;
        }

        float length() {
            return static_cast<float>(sqrt(lengthSquared()));
        }
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
