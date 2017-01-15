//
// Created by gabriel on 10.1.2017.
//

#include "ParticleManager.h"

//void ParticleManager::addParticle(Particle particle, PointerParticleTexture texture){
//    if(particles.find(texture) == particles.end()){
//        initParticles(texture);
//    }
//    count++;
//    particles[texture].push_back(particle);
//}

void ParticleManager::initParticles(PointerParticleTexture texture){
    particles[texture] = std::vector<Particle>();
}
int ParticleManager::size(void){
    return count;
}

void ParticleManager::createSystem(PointerTexture2D texture, float pps, float speed, float gravityComplient, float lifeLength){
    PointerParticleTexture pointerTexture = textures[texture->getTitle()];
    std::shared_ptr<ParticleSystemSimple> system = std::shared_ptr<ParticleSystemSimple>(new ParticleSystemSimple(pointerTexture, this, pps, speed, gravityComplient, lifeLength));
    systems.push_back(system);
//    addParticle(Particle(pointerTexture, position, velocity, gravityEffect, lifeLength, rotation, scale));

    //    PointerParticleTexture pointerTexture = textures[texture];
//    std::shared_ptr<ParticleSystemSimple> system = std::shared_ptr<ParticleSystemSimple>(new ParticleSystemSimple(pointerTexture, this, pps, speed, gravityComplient, lifeLength));
//    systems.push_back(system);

//    if(!hasTexture(texture)){
//        std::cout << "textura " << texture << " neexistuje\n";
//        exit(1);
//    }
//    PointerParticleTexture pointerTexture = textures[texture];
//    std::shared_ptr<ParticleSystemSimple> system = std::shared_ptr<ParticleSystemSimple>(new ParticleSystemSimple(pointerTexture, this, pps, speed, gravityComplient, lifeLength));
//    systems.push_back(system);
}

void ParticleManager::addParticle(Particle particle){
    if(particles.find(particle.getTexture()) == particles.end()){
        initParticles(particle.getTexture());
    }
    count++;
    particles[particle.getTexture()].push_back(particle);
}

void ParticleManager::update(float delta){
    for (auto it = particles.begin(); it != particles.end(); ++it){ //pre všetky texture
        if(it -> second.size()){
            auto itPart = it->second.begin();
            while(itPart != it->second.end()){ //prejde všetky častice
                bool stillAlive = itPart -> update(delta);
                if(stillAlive){
                    itPart++;
                }
                else{
                    count--;
                    itPart = it->second.erase(itPart);
                }
            }
        }
    }
    for(auto system : systems){
        system ->update(delta, Vector3f(5, 5, 5));
    }
}
bool ParticleManager::hasTexture(std::string name){
    return textures.find(name) != textures.end();
}
void ParticleManager::loadTexture(PointerTexture2D texture, int rows, int columns){;
    if(!hasTexture(texture -> getTitle())){
        textures[texture -> getTitle()] = PointerParticleTexture(new ParticleTexture(texture, rows, columns));
    }
}
void ParticleManager::createParticle(PointerTexture2D texture, const Vector3f &position, const Vector3f &velocity, float gravityEffect, float lifeLength, float rotation, float scale){
    PointerParticleTexture pointerTexture = textures[texture -> getTitle()];
    addParticle(Particle(pointerTexture, position, velocity, gravityEffect, lifeLength, rotation, scale));
}