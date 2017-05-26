//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLEMANAGER_H
#define GRAPHICSPROJECT_PARTICLEMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <src/utils/resources/FileLoader.h>
#include "Particle.h"

//class ParticleSystemSimple;
class Emitter;

class ParticleManager {
private:
    uint count = 0;
    std::map<std::string, PointerParticleTexture> textures;
    std::vector<Emitter*> emitters;
    ParticlesList particles;

    inline void initParticles(PointerParticleTexture texture){
        particles[texture] = std::vector<Particle>();
    }
public:
    inline ParticlesList getParticles(void) const{return particles; }
    inline uint size(void) const{return count; }

    inline void addEmitter(Emitter* emitter){ emitters.push_back(emitter); }

    inline PointerParticleTexture getTexture(const std::string& texture){ return textures[texture]; }

    inline void addParticle(const Particle& particle){
        if(particles.find(particle.getTexture()) == particles.end()){
            initParticles(particle.getTexture());
        }
        count++;
        particles[particle.getTexture()].push_back(particle);
    }
    void update(const float delta);

    inline bool hasTexture(const std::string& name) const{return MAP_CONTAINS_KEY(textures, name); }

    inline void loadTexture(const PointerTexture2D texture, const uint rows, const uint columns){;
        if(!hasTexture(texture -> getTitle())){
            textures[texture -> getTitle()] = PointerParticleTexture(new ParticleTexture(texture, rows, columns));
        }
    }
    inline void createParticle(const PointerTexture2D texture,
                               const Vector3f &position,
                               const Vector3f &velocity,
                               const float gravityEffect,
                               const float lifeLength,
                               const float rotation,
                               const float scale){
        PointerParticleTexture pointerTexture = textures[texture -> getTitle()];
        addParticle(Particle(pointerTexture, position, velocity, gravityEffect, lifeLength, rotation, scale));
    }
};

#endif //GRAPHICSPROJECT_PARTICLEMANAGER_H
