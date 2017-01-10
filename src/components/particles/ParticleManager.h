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


typedef std::map<PointerParticleTexture, std::vector<Particle>> ParticlesList;
class ParticleManager {
private:
    std::map<std::string, PointerParticleTexture> textures;
    ParticlesList particles;
    std::vector<PointerParticleSystemSimple> systems;
    void addParticle(Particle particle, PointerParticleTexture texture){
        if(particles.find(texture) == particles.end()){
            initParticles(texture);
        }
        particles[texture].push_back(particle);
    }

    void initParticles(PointerParticleTexture texture){
        particles[texture] = std::vector<Particle>();
    }
public:
    void addParticle(Particle particle){
        PointerParticleTexture texture = particle.getTexture();
        if(particles.find(texture) == particles.end()){
            std::cout << "textura neexistuje\n";
            exit(1);
        }
        particles[texture].push_back(particle);
    }
    void update(float delta){
        for (auto it = particles.begin(); it != particles.end(); ++it){ //pre všetky texture
            if(it -> second.size()){
                auto itPart = it->second.begin();
                while(itPart != it->second.end()){ //prejde všetky častice
                    bool stillAlive = itPart -> update(delta);
                    if(stillAlive){
                        itPart++;
                    }
                    else{
                        itPart = it->second.erase(itPart);
                    }
                }
            }
        }
    }

    void loadTexture(std::string name, int rows, int columns){;
        if(textures.find(name) == textures.end()){
            textures[name] = PointerParticleTexture(new ParticleTexture(ContentLoader::loadTexturePNG(name), rows, columns));
        }
    }
    void createSystem(std::string texture, float pps, float speed, float gravityComplient, float lifeLength){
        if(textures.find(texture) == textures.end()){
            std::cout << "textura " << texture << " neexistuje\n";
            exit(1);
        }
        PointerParticleTexture pointerTexture = textures[texture];
        PointerParticleSystemSimple system = PointerParticleSystemSimple(new ParticleSystemSimple(pointerTexture, nullptr, pps, speed, gravityComplient, lifeLength));
        systems.push_back(system);
    }
    void createParticle(std::string texture, const Vector3f &position, const Vector3f &velocity, float gravityEffect, float lifeLength, float rotation, float scale){
        if(textures.find(texture) == textures.end()){
            std::cout << "textura " << texture << " neexistuje\n";
            exit(1);
        }
        PointerParticleTexture pointerTexture = textures[texture];
        addParticle(Particle(pointerTexture, position, velocity, gravityEffect, lifeLength, rotation, scale), pointerTexture);
    }
};


#endif //GRAPHICSPROJECT_PARTICLEMANAGER_H
