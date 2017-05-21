//
// Created by gabriel on 10.1.2017.
//

#include "ParticleManager.h"
#include "ParticleSystemSimple.h"

void ParticleManager::createSystem(PointerTexture2D texture, float pps, float speed, float gravityComplient, float lifeLength){
    PointerParticleTexture pointerTexture = textures[texture->getTitle()];
    std::shared_ptr<ParticleSystemSimple> system = std::shared_ptr<ParticleSystemSimple>(new ParticleSystemSimple(pointerTexture, *this, pps, speed, gravityComplient, lifeLength));
    systems.push_back(system);
}

void ParticleManager::update(float delta){
    ITERATE_MAP_AUTO(particles, it){ //pre všetky textury
        if(it -> second.size()){
            ITERATE_VECTOR_ITERATOR_AUTO_ENDLESS(it->second, itPart){ //prejde všetky častice
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
    ITERATE_VECTOR(systems, i){
        systems[i] -> update(delta, Vector3f(5, 5, 5));
    }
    for(auto system : systems){
        system ->update(delta, Vector3f(5, 5, 5));
    }
}





