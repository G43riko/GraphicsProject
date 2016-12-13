//
// Created by gabriel on 10.12.2016.
//

#ifndef GRAPHICSPROJECT_THROWINGAX_H
#define GRAPHICSPROJECT_THROWINGAX_H


#include "GameObject.h"
#include "Environment.h"
#include "Ball.h"

class Arrow :public GameObject{
private:
    Environment * environment = nullptr;
public:
    Arrow(PointerEntity object, Vector3f vel, Environment * env = nullptr) : GameObject(object){
        environment = env;
        velocity = vel;
    }

    void update(float delta){
        object -> getTransform() -> move(velocity * delta);
        velocity += (*environment).getAllForces();
        if(object->getTransform()->getPosition()->y < 0)
            object ->setAlive(false);


        for (Ball * b : Ball::balls) {
            if(!b->getObject()->isAlive())
                continue;
            Vector3f dist = *b->getObject()->getTransform()->getPosition() - object->getTransform()->getPosition();

            if(dist.getLength() < Ball::size * 2){
                b->getObject()->setAlive(false);
                object->setAlive(false);
                return;
            }
        }
    }
};


#endif //GRAPHICSPROJECT_THROWINGAX_H
