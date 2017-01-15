//
// Created by gabriel on 9.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H
#define GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H


#include <src/utils/Vectors.h>
#include "ParticleManager.h"

class ParticleManager;

class ParticleSystemSimple {
private:
    float pps;
    float speed;
    float gravityComplient;
    float lifeLength;
    ParticleManager *parent;
    PointerParticleTexture texture;
public:
    ParticleSystemSimple(PointerParticleTexture texture, ParticleManager *parent, float pps, float speed, float gravityComplient, float lifeLength) : texture(texture) {
        this->parent = parent;
        this->pps = pps;
        this->speed = speed;
        this->gravityComplient = gravityComplient;
        this->lifeLength = lifeLength;
    }

    void update(float delta, Vector3f systemCenter) {
        float particlesToCreate = pps * delta;
        int count = (int) floor(particlesToCreate);
        float partialParticle = (float) fmod(particlesToCreate, 1);
        for (int i = 0; i < count; i++) {
            emitParticle(systemCenter);
        }
        if (((double) rand() / (RAND_MAX)) + 1 < partialParticle) {
            emitParticle(systemCenter);
        }
    }

    void emitParticle(Vector3f center);
};

#endif //GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H
