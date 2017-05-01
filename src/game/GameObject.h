//
// Created by gabriel on 27.11.2016.
//

#ifndef GRAPHICSPROJECT_GAMEOBJECT_H
#define GRAPHICSPROJECT_GAMEOBJECT_H

#include <src/rendering/model/Entity.h>

class GameObject{
protected:
    PointerEntity object = nullptr;
    Vector3f velocity;
public:
    GameObject(PointerEntity object){
        this -> object = object;
    }
    virtual void update(float delta){
        object -> move(velocity.x, velocity.y, velocity.z);
    }
    inline void setVelocity(const Vector3f & value){
        velocity = value;
    }

    inline PointerEntity getObject(void) const{
        return object;
    }
    inline Vector3f * getVelocity(void){
        return &velocity;
    }
};
typedef std::shared_ptr<GameObject> PointerGameObject;

#endif //GRAPHICSPROJECT_GAMEOBJECT_H
