//
// Created by gabriel on 10.1.2017.
//

#include "ParticleManager.h"
#include "emitters/Emitter.h"


void ParticleManager::update(const float delta){
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
    ITERATE_VECTOR(emitters, i){
        emitters[i] -> update(delta, Vector3f(5, 5, 5));
    }

}





