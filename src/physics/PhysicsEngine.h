//
// Created by gabriel on 17.5.2017.
//

#ifndef GAMEENGINE_PHYSICSENGINE_H
#define GAMEENGINE_PHYSICSENGINE_H

#include <vector>
#include "PhysicsObject.h"
#include "IntersectData.h"

class PhysicsEngine{
    std::vector<PhysicsObject> _objects;
public:
    inline void addObject(const PhysicsObject& object){
        _objects.push_back(object);
    }

    inline void simulate(const float delta){
        for(unsigned int i=0 ; i<_objects.size() ; i++){
            _objects[i].integrage(delta);
        }
    }

    inline void handleCollisions(const float delta){
        ITERATE_VECTOR(_objects, i){
            for(uint j=i+1 ; j<_objects.size() ; j++) {
                IntersectData intersectData = _objects[i].getColider().intersect(_objects[j].getColider());
                if(intersectData.isIntersect()){
                    Vector3f direction = intersectData.getDirection().getNormal();
                    Vector3f otherDirection = Vector3f(direction.reflect(_objects[i].getVelocity().getNormal()));

                    _objects[i].setVelocity(_objects[i].getVelocity().reflect(otherDirection));
                    _objects[j].setVelocity(_objects[j].getVelocity().reflect(direction));
                }
            }
        }
    }

    inline const PhysicsObject& getObject(const uint index) const{
        return _objects[index];
    }
    inline unsigned int getNumObjects(void) const{
        return (unsigned int)_objects.size();
    }
};

#endif //GAMEENGINE_PHYSICSENGINE_H
