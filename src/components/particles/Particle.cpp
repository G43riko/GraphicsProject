//
// Created by gabriel on 18.11.2016.
//

#include "Particle.h"
Particle::Particle(PointerParticleTexture texture, const Vector3f &position, const Vector3f &velocity, float gravityEffect, float lifeLength, float rotation, float scale)
    :texture(texture){
    this -> position = position;
    this -> velocity = velocity;
    this -> gravityEffect = gravityEffect;
    this -> lifeLength = lifeLength;
    this -> rotation = rotation;
    this -> scale = scale;
}

bool Particle::update(float delta){
    velocity.y += gravityEffect * delta * GRAVITY;
    position += velocity * delta;
    elapsedTime += delta;
    updateTextureCoordInfo();
    return elapsedTime < lifeLength;
}
Vector3f Particle::getPosition(void){
    return position;
}
float Particle::getRotation(void){
    return rotation;
}
float Particle::getScale(void){
    return scale;
}