//
// Created by gabriel on 27.11.2016.
//

#include "Ball.h"

float Ball::GRAVITY_EFFECT = 0.8f;
float Ball::DEFRACTION_EFFECT = 0.95f;
std::vector<Ball*> Ball::balls;

Ball::Ball(PointerEntity object) : GameObject(object){
        balls.push_back(this);
};

void Ball::update(float delta){
    if(!getObject() -> isAlive())
        return;
    object -> getTransform() -> move(velocity * delta);
    object -> getTransform() -> getRotation() -> rotate(Vector3f(-velocity.z * 0.4f, 0.0f, velocity.x * 0.4f) * delta);
    checkCollision(this);
    //float DEFRACTION_EFFECT = 0.95f;
    velocity *= Ball::DEFRACTION_EFFECT * delta;

//        if(velocity.x != 0)
//            velocity.x += velocity.x > 0 ? -DEFRACTION_EFFECT : DEFRACTION_EFFECT;
//        if(velocity.y != 0)
//            velocity.y += velocity.y > 0 ? -DEFRACTION_EFFECT : DEFRACTION_EFFECT;
//        if(velocity.z != 0)
//            velocity.z += velocity.z > 0 ? -DEFRACTION_EFFECT : DEFRACTION_EFFECT;
//        if(abs(velocity.x) < DEFRACTION_EFFECT)
//            velocity.x = 0;
//        if(abs(velocity.y) < DEFRACTION_EFFECT)
//            velocity.y = 0;
//        if(abs(velocity.z) < DEFRACTION_EFFECT)
//            velocity.z = 0;
}