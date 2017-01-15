//
// Created by gabriel on 9.1.2017.
//

#include "ParticleSystemSimple.h"

void ParticleSystemSimple::emitParticle(Vector3f center){
    Vector3f velocity = Vector3f(random(-1.0f, 1.0f), 1.0, random(-1.0f, 1.0f));
    velocity.normalize();
    parent -> createParticle(texture->texture, Vector3f(center), velocity * speed, gravityComplient, lifeLength, 0, 1);
    //scene -> addParticle(Particle(texture, Vector3f(center), velocity * speed, gravityComplient, lifeLength, 0, 1));
}