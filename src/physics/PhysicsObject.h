//
// Created by gabriel on 17.5.2017.
//

#ifndef GAMEENGINE_PHYSICSOBJECT_H
#define GAMEENGINE_PHYSICSOBJECT_H

#include <src/utils/math/objects/Vectors.h>
#include "Collider.h"

class PhysicsObject{
    Vector3f _position;
    Vector3f _velocity;
    Collider * _colider;
public:
//    inline PhysicsObject(const Vector3f& position, const Vector3f& velocity) : _position(position), _velocity(velocity){}
    inline PhysicsObject(Collider *colider, const Vector3f& velocity) : _colider(colider), _velocity(velocity){}
//    inline const Vector3f& getPosition(void) const{return _position;}
    inline const Vector3f& getVelocity(void) const{return _velocity;}
    inline const Collider& getColider(void) const{return *_colider;}
    inline void setVelocity(const Vector3f& velocity){_velocity = velocity;}
    inline void integrage(float delta){
        _position += _velocity * delta;
    }
};

#endif //GAMEENGINE_PHYSICSOBJECT_H
