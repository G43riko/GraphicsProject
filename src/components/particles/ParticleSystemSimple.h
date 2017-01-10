//
// Created by gabriel on 9.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H
#define GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H


#include <src/utils/Vectors.h>
#include <src/game/Scene.h>

class ParticleSystemSimple {
private:
    float pps;
    float speed;
    float gravityComplient;
    float lifeLength;
    Scene * scene;
    PointerParticleTexture texture;
public:
    ParticleSystemSimple(PointerParticleTexture texture, Scene * scene, float pps, float speed, float gravityComplient, float lifeLength) : texture(texture){
        this -> scene = scene;
        this -> pps = pps;
        this -> speed = speed;
        this -> gravityComplient = gravityComplient;
        this -> lifeLength = lifeLength;
    }

void update(float delta, Vector3f systemCenter){
        float particlesToCreate = pps * delta;
        int count = (int) floor(particlesToCreate);
        float partialParticle = (float)fmod(particlesToCreate, 1);
        for(int i=0;i<count;i++){
            emitParticle(systemCenter);
        }
        if(((double) rand() / (RAND_MAX)) + 1 < partialParticle){
            emitParticle(systemCenter);
        }
    }

void emitParticle(Vector3f center){
        float dirX = (float) (((double) rand() / (RAND_MAX)) + 1) * 2.0f - 1.0f;
        float dirZ = (float) (((double) rand() / (RAND_MAX)) + 1) * 2.0f - 1.0f;
        Vector3f velocity = Vector3f(dirX, 1.0f, dirZ);
        velocity.normalize();
        scene -> addParticle(Particle(texture, Vector3f(center), velocity * speed, gravityComplient, lifeLength, 0, 1));
    }
};

typedef std::shared_ptr<ParticleSystemSimple> PointerParticleSystemSimple;

#endif //GRAPHICSPROJECT_PARTICLESYSTEMSIMPLE_H
