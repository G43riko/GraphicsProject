//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLEMASTER_H
#define GRAPHICSPROJECT_PARTICLEMASTER_H

#include <src/rendering/RenderUtil.h>
#include "Particle.h"

class ParticleMaster {
private:
    PointerRawModel model;
    PointerBasicShader shader;
    RenderUtil * utils;
public:
    void renderParticles(std::vector<Particle> sky, PointerCamera camera);
    ParticleMaster(RenderUtil * utils, PointerBasicShader shader, Loader loader) : shader(shader), utils(utils){
        std::vector<float> vertices = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f};
        model = loader.loadToVao(vertices, 2);
    }
};


#endif //GRAPHICSPROJECT_PARTICLEMASTER_H
