//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLEMASTER_H
#define GRAPHICSPROJECT_PARTICLEMASTER_H

#include <src/rendering/RenderUtil.h>
#include "Particle.h"

class ParticleMaster {
private:
    PointerBasicShader shader;
    RenderUtil * utils;
public:
    void renderParticles(std::vector<Particle> sky, PointerRawModel model, PointerCamera camera);
    ParticleMaster(RenderUtil * utils, PointerBasicShader shader) : shader(shader), utils(utils){}
};


#endif //GRAPHICSPROJECT_PARTICLEMASTER_H
