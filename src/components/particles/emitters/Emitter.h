//
// Created by gabriel on 20.5.2017.
//

#ifndef GAMEENGINE_EMITTER_H
#define GAMEENGINE_EMITTER_H

#include <src/components/particles/ParticleManager.h>

//BoxEmitter vec3 min, vec3 max
//DirectionalEmitter -> vec3 direction, float cutoff
//RingEmitter -> ??? niečo ako plane?
//sphereEmitter -> vec3 center, radius
//lineEmitter -> vec3 start, vec3 end, randomness

class Emitter{
    const float pps;    //particles per seconds
    const float speed;
    const float gravityComplient;
    const float lifeLength;
protected:
    ParticleManager parent;
    const PointerParticleTexture texture;

    virtual void emitParticle(const Vector3f& center){
        Vector3f velocity = Vector3f(grandom(-1.0f, 1.0f), 1.0, grandom(-1.0f, 1.0f)).normalize();
        parent.createParticle(texture -> getTexture(),
                              center,
                              velocity * speed,
                              gravityComplient,
                              lifeLength, 0, 1);
    };
public:
    inline Emitter(PointerParticleTexture texture,
                   ParticleManager& parent,
                   float pps,
                   float speed,
                   float gravityComplient,
                   float lifeLength) :
            pps(pps),
            speed(speed),
            gravityComplient(gravityComplient),
            lifeLength(lifeLength),
            parent(parent),
            texture(texture){}

    virtual void update(const float delta, const Vector3f& systemCenter) {
        const float particlesToCreate = pps * delta;
        const uint count = (uint) floor(particlesToCreate);
        const float partialParticle = (float) fmod(particlesToCreate, 1);
        LOOP_U(count, i){
            emitParticle(systemCenter);
        }
        if (((double) rand() / (RAND_MAX)) + 1 < partialParticle) {
            emitParticle(systemCenter);
        }
    }
};

#endif //GAMEENGINE_EMITTER_H
