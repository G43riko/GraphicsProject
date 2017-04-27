//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_TRANSFORM_H
#define GRAPHICSPROJECT_TRANSFORM_H

#include "Quaternion.h"
#include "src/utils/Maths.h"
template<typename T>
inline T linearInterpolation(const T &a, const T &b, const float &val){
    return a * val + b * (1 - val);
}
class Transform {
private:
    Vector3f position;
    Quaternion rotation;
    Vector3f scale;
    Vector3f parentAttributes = Vector3f(1, 1, 1);
    Transform * parent = nullptr;


public:
    Transform(){};
    inline Transform(Vector3f position, Vector3f rotation, Vector3f scale) {
        init(position, rotation, scale);
    }
    inline void init(const Vector3f &position, const Vector3f &rotation, const Vector3f &scale) {
        this -> position = position;
        this -> rotation.rotate(rotation);
        this -> scale = scale;
    }
    inline void move(float x, float y, float z){
        position.x += x;
        position.y += y;
        position.z += z;
    }

    inline void move(const Vector3f & dir){
        move(dir.x, dir.y, dir.z);
    };
    //void rotate(float, float, float);


    inline void rotate(const Quaternion& rot) {
        rotation = Quaternion(rot.mul(rotation).normalize());
    }
    inline void rotate(const Vector3f& axis, float angle){
        rotate(Quaternion(axis, angle));
    }
    inline Matrix4f getTransformation(bool pos = true, bool rot = true, bool sca = true) const{
        Matrix4f result;
        Matrix4f::setIdentity(result);
        if (parent) {
            result = parent -> getTransformation(parentAttributes.x > 0, parentAttributes.y > 0, parentAttributes.z > 0) *
                     result;
        }
        if (pos){
            result = Matrix4f::initTranslation(position.x, position.y, position.z) * result;
        }
        if (rot){
            result = rotation.toRotationMatrix() * result;
        }
        if(sca){
            result = Matrix4f::initScale(scale.x, scale.y, scale.z) * result;
        }
        return result;
    }

    inline Vector3f * getScale(void){return &scale;}
    inline Vector3f * getPosition(void){return &position;}
    inline Quaternion * getRotation(void){return &rotation;}

    inline float getPosX(void) const{return position.x;}
    inline float getPosY(void) const{return position.y;}
    inline float getPosZ(void) const{return position.z;}

    inline float getScaleX(void) const{return scale.x;}
    inline float getScaleY(void) const{return scale.y;}
    inline float getScaleZ(void) const{return scale.z;}

    inline Matrix4f getAverageTransformation(Transform a, Transform b, float ratio) const{
        Vector3f pos = linearInterpolation(*a.getPosition(), *b.getPosition(), ratio);
        //Quaternion rot = Quaternion::slerp(*a.getRotation(), *b.getRotation(), ratio); //linearInterpolation(*a.getRotation(), *b.getRotation(), ratio);
        Vector3f scale = linearInterpolation(*a.getScale(), *b.getScale(), ratio);
        return Transform(pos, a.getRotation() -> getForward(), scale).getTransformation(true, false, true);
    }

    inline void setRotation(Quaternion q){
        rotation = q;
    }

    inline void setPosition(Vector3f vec){
        position = vec;
    }
    inline void setParent(Transform * parent, bool pos, bool rot, bool scale){
        this -> parent = parent;
        parentAttributes.x = pos ? 1 : 0;
        parentAttributes.y = rot ? 1 : 0;
        parentAttributes.z = scale ? 1 : 0;
    }

};

#endif //GRAPHICSPROJECT_TRANSFORM_H
