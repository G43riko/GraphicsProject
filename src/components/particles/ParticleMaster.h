//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLEMASTER_H
#define GRAPHICSPROJECT_PARTICLEMASTER_H

#include <src/rendering/RenderUtil.h>
#include "src/rendering/shader/ParticleShader.h"
#include "Particle.h"
#include "ParticleManager.h"

class ParticleMaster {
    BasicShader * shader = new ParticleShader();
    const PointerRawModel model;
public:
    void renderParticles(ParticlesList particles, PointerCamera camera);
    void renderParticles(std::vector<Particle> particles, PointerCamera camera);

    ParticleMaster(PointerCamera camera, Loader loader) :
            model(loader.loadToVao(PARTICLE_VERTICES, 2)){
        RenderUtil::updateProjectionMatrix(*shader, camera);
    };
    void cleanUp(void){};
};


#endif //GRAPHICSPROJECT_PARTICLEMASTER_H
