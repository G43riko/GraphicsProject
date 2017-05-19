//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLEMANAGER_H
#define GRAPHICSPROJECT_PARTICLEMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <src/utils/resources/FileLoader.h>
#include "ParticleTexture.h"
#include "Particle.h"

class ParticleSystemSimple;

class ParticleManager {
private:
    int count = 0;
    std::map<std::string, PointerParticleTexture> textures;
    std::vector<std::shared_ptr<ParticleSystemSimple>> systems;
    ParticlesList particles;

//    void addParticle(Particle particle, PointerParticleTexture texture);
    inline void initParticles(PointerParticleTexture texture){
        particles[texture] = std::vector<Particle>();
    }


public:
    inline ParticlesList getParticles(void) const{return particles; }
    inline int size(void) const{return count; }

    void createSystem(PointerTexture2D texture, float pps, float speed, float gravityComplient, float lifeLength);
    inline void addParticle(Particle particle){
        if(particles.find(particle.getTexture()) == particles.end()){
            initParticles(particle.getTexture());
        }
        count++;
        particles[particle.getTexture()].push_back(particle);
    }
    void update(float delta);
    inline bool hasTexture(std::string name) const{return textures.find(name) != textures.end(); }
    inline void loadTexture(PointerTexture2D texture, int rows, int columns){;
        if(!hasTexture(texture -> getTitle())){
            textures[texture -> getTitle()] = PointerParticleTexture(new ParticleTexture(texture, rows, columns));
        }
    }
    inline void createParticle(PointerTexture2D texture, const Vector3f &position, const Vector3f &velocity, float gravityEffect, float lifeLength, float rotation, float scale){
        PointerParticleTexture pointerTexture = textures[texture -> getTitle()];
        addParticle(Particle(pointerTexture, position, velocity, gravityEffect, lifeLength, rotation, scale));
    }
};

#endif //GRAPHICSPROJECT_PARTICLEMANAGER_H
