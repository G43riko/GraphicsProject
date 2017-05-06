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
    float reflectance = 0.0f;
    float _gravityEffect = 0;
public:
    GameObject(PointerEntity object){
        this -> object = object;
    }
    virtual void hitFloor(float height){
        if(NEZ(reflectance)){
            object->getTransform()->getPosition()->setY(height);
            velocity.y *= -reflectance;
        }
        else{
            velocity.x = velocity.y = velocity.z = 0;
            object->getTransform()->getPosition()->setY(height);
        }
    }
    virtual void update(float delta){
        if(NEZ(_gravityEffect) && NEZ(velocity.y)){
            velocity.y += GRAVITY * _gravityEffect;
        }
        object -> move(velocity.x, velocity.y, velocity.z);
    }

    inline Vector3f getNextPos(void) const{
        return *object->getTransform()->getPosition() + velocity;
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

    inline void setGravityEffect(float gravityEffect){
        _gravityEffect = gravityEffect;
    }
};
typedef std::shared_ptr<GameObject> PointerGameObject;

#endif //GRAPHICSPROJECT_GAMEOBJECT_H
