//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLEMASTER_H
#define GRAPHICSPROJECT_PARTICLEMASTER_H

#include <src/rendering/RenderUtil.h>
#include "Particle.h"
#include "ParticleManager.h"

class ParticleMaster {
private:
    PointerRawModel model;
    PointerBasicShader shader;
public:
    void renderParticles(ParticlesList particles, PointerCamera camera);
    void renderParticles(std::vector<Particle> particles, PointerCamera camera);
    ParticleMaster(PointerBasicShader shader, Loader loader) : shader(shader){
        std::vector<float> vertices = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f};
        model = loader.loadToVao(vertices, 2);
    };
    void cleanUp(void){};
};


#endif //GRAPHICSPROJECT_PARTICLEMASTER_H
