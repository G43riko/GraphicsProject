//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLEMASTER_H
#define GRAPHICSPROJECT_PARTICLEMASTER_H

#include <src/rendering/RenderUtil.h>
#include "Particle.h"
#include "ParticleManager.h"

class ParticleMaster {
    const PointerBasicShader shader;
    const PointerRawModel model;
public:
    void renderParticles(ParticlesList particles, PointerCamera camera);
    void renderParticles(std::vector<Particle> particles, PointerCamera camera);
    ParticleMaster(PointerBasicShader shader, Loader loader) :
            shader(shader),
            model(loader.loadToVao(PARTICLE_VERTICES, 2)){};
    void cleanUp(void){};
};


#endif //GRAPHICSPROJECT_PARTICLEMASTER_H
