//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_VECTORS_H
#define GRAPHICSPROJECT_VECTORS_H

#include <iostream>
#include <string.h>
#include <memory>
#include <math.h>
#include "src/utils/GUtils.h"

#define VECTOR_DIVIDER "_"

class Vector3f;

class Vector4f;
typedef std::shared_ptr<Vector3f> PointerVector3f;
class Quaternion;
class Vector2f{
private:
public:
    float x = 0.0f, y = 0.0f;
    /*CONSTRUCTORS*/
    inline Vector2f(void){};
    inline Vector2f(const Vector2f& vec) : x(vec.x), y(vec.y){};
    inline Vector2f(const int i_x, const int i_y) : x((float)i_x), y((float)i_y){};
    inline Vector2f(const float i_x, const float i_y) : x(i_x), y(i_y){};
    inline Vector2f(const double i_x, const double i_y) : x((float)i_x), y((float)i_y){};
    inline Vector2f(std::string data){
        std::string currentLine = strtok((char *)data.c_str(), VECTOR_DIVIDER);
        x = static_cast<float>(atof(currentLine.c_str() + 1));
        currentLine = strtok(NULL, VECTOR_DIVIDER);
        y = static_cast<float>(atof(currentLine.c_str()));
    }

    /*OPERATORS*/
    inline Vector2f& operator *= (const float& v){ x *= v, y *= v;return *this; }
    inline Vector2f operator *= (const Vector2f& v){ x *= v.x, y *= v.y;return *this; }
    inline Vector2f operator * (const Vector2f &v)const{ return Vector2f(x * v.x, y * v.y); }
    inline Vector2f operator * (const float& v)const{ return Vector2f(x * v, y * v); }

    inline Vector2f& operator /= (const float& v){ x /= v, y /= v;return *this; }
    inline Vector2f operator /= (const Vector2f& v){ x /= v.x, y /= v.y;return *this; }
    inline Vector2f operator / (const Vector2f &v) const{ return Vector2f(x / v.x, y / v.y); }
    inline Vector2f operator / (const float& v)const{ return Vector2f(x / v, y / v); }

    inline Vector2f& operator += (const float& v){ x += v, y += v;return *this; }
    inline Vector2f operator += (const Vector2f& v){ x += v.x, y += v.y;return *this; }
    inline Vector2f operator + (const Vector2f &v)const{ return Vector2f(x + v.x, y + v.y); }
    inline Vector2f operator + (const float& v)const{ return Vector2f(x + v, y + v); }

    inline Vector2f& operator -= (const float& v){ x -= v, y -= v;return *this; }
    inline Vector2f operator -= (const Vector2f& v){ x -= v.x, y -= v.y;return *this; }
    inline Vector2f operator - (const Vector2f &v)const{ return Vector2f(x - v.x, y - v.y); }
    inline Vector2f operator - (const float& v)const{ return Vector2f(x - v, y - v); }


    inline Vector2f operator >> (const Vector2f &v)const{ return Vector2f(getXi() >> v.getXi(), getYi() >> v.getYi()); }
    inline Vector2f operator >> (const int& v)const{ return Vector2f(getXi() >> v, getYi() >> v); }

    inline Vector2f operator << (const Vector2f &v)const{ return Vector2f(getXi() << v.getXi(), getYi() << v.getYi()); }
    inline Vector2f operator << (const int& v)const{ return Vector2f(getXi() << v, getYi() << v); }

    inline Vector2f& operator = (const Vector2f& v){x = v.x, y = v.y;return *this;}

    inline friend std::ostream& operator << (std::ostream& os, const Vector2f& v){
        os << "[" << v.x << ", " << v.y << "]";
        return os;
    };

    /*OTHERS*/
    inline float lengthSquared() const{return x * x + y * y;}
    inline float length(void) const{return (float)sqrt(x * x + y * y);}
    inline Vector2f getNormal(void)const {float l = (float)sqrt(x * x + y * y); return Vector2f(x / l, y / l);}
    inline Vector2f& normalize(void){float l = (float)sqrt(x * x + y * y); x /= l, y /= l;return *this;}

    inline std::string toString(void) const{return "[" + std::to_string(x) + VECTOR_DIVIDER + std::to_string(y) + "]";}
    inline float dot(const Vector2f& vec) const{return x * vec.x + y * vec.y;}

    inline void show(std::string text = "", bool breakLine = true) const{
        printf("%s[%f, %f]%c", text.empty() ? "" : (text + ": ").c_str(), x, y, breakLine ? '\n' : ' ');
    }
    /*GETTERS*/
    inline float getX(void) const{return x;}
    inline float getY(void) const{return y;}
    inline int getXi(void) const{return (int)x;}
    inline int getYi(void) const{return (int)y;}

    /*SETTERS*/
    inline void setX(const float i_x){x = i_x;}
    inline void setY(const float i_y){y = i_y;}
    inline void set(const float i_x, const float i_y){x = i_x, y = i_y;}
};

class Vector3f{
private:
public:
    float x = 0.0f, y = 0.0f, z = 0.0f;
    //CONSTRUCTORS
    inline Vector3f(void){};
    inline Vector3f(const Vector3f& vec) : x(vec.x), y(vec.y), z(vec.z){};
    inline Vector3f(const int i_x, const int i_y, const int i_z) : x((float)i_x), y((float)i_y), z((float)i_z){};
    inline Vector3f(const float i_x, const float i_y, const float i_z) : x(i_x), y(i_y), z(i_z){};
    inline Vector3f(const double i_x, const double i_y, const double i_z) : x((float)i_x), y((float)i_y), z((float)i_z){};
    inline Vector3f(std::string data){
        std::string currentLine = strtok((char *)data.c_str(), VECTOR_DIVIDER);
        x = static_cast<float>(atof(currentLine.c_str() + 1));
        currentLine = strtok(NULL, VECTOR_DIVIDER);
        y = static_cast<float>(atof(currentLine.c_str()));
        currentLine = strtok(NULL, VECTOR_DIVIDER);
        z = static_cast<float>(atof(currentLine.c_str()));
        std::cout << *this << "\n";
    }

    //OPERATORS
    inline Vector3f& operator *= (const float& v){ x *= v, y *= v, z *= v;return *this; }
    inline Vector3f& operator *= (const Vector3f& v){ x *= v.x, y *= v.y, z *= v.z;return *this; }
    inline Vector3f operator * (const Vector3f &v)const{ return Vector3f(x * v.x, y * v.y, z * v.z); }
    inline Vector3f operator * (const float& v)const{ return Vector3f(x * v, y * v, z * v); }

    inline Vector3f& operator /= (const float& v){ x /= v, y /= v, z /= v;return *this; }
    inline Vector3f& operator /= (const Vector3f& v){ x /= v.x, y /= v.y, z /= v.z;return *this; }
    inline Vector3f operator / (const Vector3f &v) const{ return Vector3f(x / v.x, y / v.y, z / v.z); }
    inline Vector3f operator / (const float& v)const{ return Vector3f(x / v, y / v, z / v); }

    inline Vector3f& operator += (const float& v){ x += v, y += v, z += v;return *this; }
    inline Vector3f& operator += (const Vector3f& v){ x += v.x, y += v.y, z += v.z;return *this; }
    inline Vector3f operator + (const Vector3f &v)const{ return Vector3f(x + v.x, y + v.y, z + v.z); }
    inline Vector3f operator + (const float& v)const{ return Vector3f(x + v, y + v, z + v); }

    inline Vector3f& operator -= (const float& v){ x -= v, y -= v, z -= v;return *this; }
    inline Vector3f& operator -= (const Vector3f& v){ x -= v.x, y -= v.y, z -= v.z;return *this; }
    inline Vector3f operator - (const Vector3f &v)const{ return Vector3f(x - v.x, y - v.y, z - v.z); }
    inline Vector3f operator - (const float& v)const{ return Vector3f(x - v, y - v, z - v); }

    inline Vector3f& operator = (const Vector3f& v){x = v.x, y = v.y, z = v.z;return *this;}
    inline Vector3f reflect(const Vector3f& v) const{return *this - (v * (this -> dot(v) * 2)); }

    inline Vector3f max(const Vector3f& v) const{return Vector3f(v.x < x ? x : v.x, v.y < y ? y : v.y, v.z < z ? z : v.z);}
    inline float max(void) const{const float max = x < y ? y : x; return max < z ? z : max;}
    friend std::ostream& operator << (std::ostream& os, const Vector3f& v){
        os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        return os;
    };


//OTHERS
    inline float lengthSquared() const{return x * x + y * y + z * z;}
    inline float length(void) const{return (float)sqrt(x * x + y * y + z * z);}
    inline Vector3f getNormal(void)const {float l = (float)sqrt(x * x + y * y + z * z); return Vector3f(x / l, y / l, z / l);}
    inline Vector3f& normalize(void){float l = (float)sqrt(x * x + y * y + z * z); x /= l, y /= l, z /= l;return *this;}

    inline Vector3f getInverted(void) const{return Vector3f(-x, -y, -z);}
    inline Vector3f& invert(void){x = -x, y = -y, z = -z; return *this;}

    inline float dot(const Vector3f& vec) const{return x * vec.x + y * vec.y + z * vec.z;}

    inline Vector3f getCross(const Vector3f& v) const{return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);}
    inline Vector3f& cross(const Vector3f& v){
        float x_ = y * v.z - z * v.y;
        float y_ = z * v.x - x * v.z;
        float z_ = x * v.y - y * v.x;
        x = x_, y = y_, z = z_;
        return *this;
    }
    inline void show(void) const{printf("[%f, %f, %f]\n", x, y, z);}
    inline std::string toString(void) const{return "[" + std::to_string(x) + VECTOR_DIVIDER + std::to_string(y) + VECTOR_DIVIDER + std::to_string(z) + "]";}
    //GETTERS
    inline float getX(void) const{return x;}
    inline float getY(void) const{return y;}
    inline float getZ(void) const{return z;}
    inline int getXi(void) const{return (int)x;}
    inline int getYi(void) const{return (int)y;}
    inline int getZi(void) const{return (int)z;}
    inline Vec3 getVec(void) const{return {x, y, z}; }
    inline static Vector3f interpolate(const Vector3f& a, const Vector3f& b, float value){
        return Vector3f(LERP(a.x, b.x, value), LERP(a.y, b.y, value), LERP(a.z, b.z, value));
    }
    inline Vector2f getXY(void) const {return {x, y};}
    inline Vector2f getXZ(void) const {return {x, z};}
    inline Vector2f getYZ(void) const {return {y, z};}
    inline Vector2f getYX(void) const {return {y, x};}
    inline Vector2f getZX(void) const {return {z, x};}
    inline Vector2f getZY(void) const {return {z, y};}

    //SETTERS
    inline void setX(const float i_x){x = i_x;}
    inline void setY(const float i_y){y = i_y;}
    inline void setZ(const float i_z){z = i_z;}
    inline void set(const float i_x, const float i_y, const float i_z){x = i_x, y = i_y, z = i_z;}
    //BONUS
    Vector3f rotate(const Quaternion& rotation);
};
class Vector4f{
    public:
//        static int count;
        float x, y, z, w;
        Vector4f(void) : Vector4f(0, 0, 0, 0){};
        Vector4f(float val) : Vector4f(val, val, val, val){};
        Vector4f(const Vector4f& v) : Vector4f(v.x, v.y, v.z, v.w){};
        Vector4f(float x, float y, float z, float w){
            this -> x = x;
            this -> y = y;
            this -> z = z;
            this -> w = w;
//            Vector4f::count++;
        };
//        ~Vector4f(){
//            Vector4f::count--;
//        };
        Vector4f normalize(void){
            float len = length();
            x /= len;
            y /= len;
            z /= len;
            w /= len;
            return *this;
        };
        friend bool operator == (const Vector4f &c1, const Vector4f& c2){
            return (EQ(c1.x, c2.x) &&
                    EQ(c1.y, c2.y) &&
                    EQ(c1.z, c2.z) &&
                    EQ(c1.w, c2.w));
        };
        friend bool operator != (const Vector4f &c1, const Vector4f& c2){ return !(c1 == c2);}
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
        void show(bool endLine = true){
            std::cout << toString();
            if(endLine)
                std::cout << std::endl;
        }
        std::string toString(void){
            return "[" + std::to_string(x) + " x " + std::to_string(y) + " x " + std::to_string(z) + " x " + std::to_string(w) + "]";
        }
        inline Vector3f getXYZ(void) const {return {x, y ,z};}
};
//
//template <typename T>class GVector{
//    protected:
//        T * data;
//        int size;
//    public:
//        GVector(){};
//        GVector(GVector<T> * arg){
//            data = new T[arg -> size];
//            size = arg -> size;
//            for(int i=0 ; i<arg -> size ; i++)
//                data[i] = arg -> data[i];
//
//        }
//        GVector<T> * mul(GVector<T> * arg){
//            if(arg -> size != size)
//                exit(10);
//            for(int i=0 ; i<size ; i++)
//                data[i] *= arg -> data[i];
//        };
//
//        GVector<T> * mul(T arg){
//            if(arg -> size != size)
//                exit(10);
//            for(int i=0 ; i<size ; i++)
//                data[i] *= arg;
//        };
//        GVector<T> * getMul(GVector<T> * arg){
//            return  (new GVector<T>(this)) -> mul(arg);
//        };
//        GVector<T> * getMul(float arg){
//            return  (new GVector<T>(this)) -> mul(arg);
//        };
//        void show(){
//            std::cout << "[" << data[0];
//            for(int i=1 ; i<size ; i++)
//                std::cout << ", " << data[i];
//            std::cout << "]" << std::endl;
//        }
//};
//template<typename T> class GVector3 : public GVector<T>{
//public:
//    template<typename S>
//    GVector3(S x, S y, S z) : GVector3(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)){}
//    GVector3(GVector3<T> * a) : GVector3(a -> getX(), a -> getY(), a -> getZ()) {};
//    GVector3(T x, T y, T z){
//        this -> size = 3;
//        this -> data = new T[this -> size]{x, y, z};
//    }
//
//    T getX(){return this -> data[0];}
//    T getY(){return this -> data[1];}
//    T getZ(){return this -> data[2];}
//};

#endif //GRAPHICSPROJECT_VECTORS_H
