//
// Created by gabriel on 18.11.2016.
//

#ifndef GRAPHICSPROJECT_PARTICLE_H
#define GRAPHICSPROJECT_PARTICLE_H

#include <src/utils/Const.h>
#include <src/utils/Vectors.h>
#include "ParticleTexture.h"


class Particle {
    private:
        Vector3f position;
        Vector3f velocity;
        float gravityEffect;
        float lifeLength;
        float rotation;
        float scale;
        PointerParticleTexture texture;
        float elapsedTime = 0;
public:
    Particle(PointerParticleTexture texture, const Vector3f &, const Vector3f &, float, float, float, float);

    bool update(float);
    Vector3f getPosition(void);
    float getRotation(void);
    float getScale(void);

    PointerParticleTexture getTexture(void){
        return texture;
    };
};


#endif //GRAPHICSPROJECT_PARTICLE_H
