//
// Created by gabriel on 9.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H
#define GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H


#include <src/utils/math/objects/Vectors.h>
#include "ParticleManager.h"

class ParticleManager;

class ParticleSystemSimple {
private:
    const float pps;
    const float speed;
    const float gravityComplient;
    const float lifeLength;

    ParticleManager parent;

    const PointerParticleTexture texture;
public:
    inline ParticleSystemSimple(PointerParticleTexture texture, ParticleManager& parent, float pps, float speed, float gravityComplient, float lifeLength) :
            pps(pps),
            speed(speed),
            gravityComplient(gravityComplient),
            lifeLength(lifeLength),
            parent(parent),
            texture(texture){}

    inline void update(float delta, Vector3f systemCenter) {
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

//    void emitParticle(Vector3f center);
    void emitParticle(Vector3f center){
        Vector3f velocity = Vector3f(grandom(-1.0f, 1.0f), 1.0, grandom(-1.0f, 1.0f)).normalize();
        parent.createParticle(texture -> getTexture(),
                              center,
                              velocity * speed,
                              gravityComplient,
                              lifeLength, 0, 1);
    }
};

#endif //GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H
