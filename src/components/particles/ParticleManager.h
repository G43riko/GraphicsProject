//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLEMANAGER_H
#define GRAPHICSPROJECT_PARTICLEMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <src/utils/FileLoader.h>
#include "ParticleTexture.h"
#include "Particle.h"
#include "ParticleSystemSimple.h"

class ParticleSystemSimple;
typedef std::map<PointerParticleTexture, std::vector<Particle>> ParticlesList;

class ParticleManager {
private:
    int count = 0;
    std::map<std::string, PointerParticleTexture> textures;
    std::vector<std::shared_ptr<ParticleSystemSimple>> systems;
    ParticlesList particles;

//    void addParticle(Particle particle, PointerParticleTexture texture);
    void initParticles(PointerParticleTexture texture);
public:
    ParticlesList getParticles(void){
        return particles;
    }
    int size(void);
    void addParticle(Particle particle);
    void update(float delta);
    bool hasTexture(std::string name);
    void loadTexture(PointerTexture2D texture, int rows, int columns);
    void createParticle(PointerTexture2D texture, const Vector3f &position, const Vector3f &velocity, float gravityEffect, float lifeLength, float rotation, float scale);
    void createSystem(PointerTexture2D texture, float pps, float speed, float gravityComplient, float lifeLength);
};

#endif //GRAPHICSPROJECT_PARTICLEMANAGER_H
