//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_SKYMASTER_H
#define GRAPHICSPROJECT_SKYMASTER_H

#include <src/rendering/material/CubeTexture.h>
#include <src/rendering/RenderUtil.h>

class SkyBoxMaster {
private:
    PointerBasicShader shader;
    RenderUtil * utils;
public:
    void renderSky(CubeTexture sky, PointerRawModel model, PointerCamera camera);
    SkyBoxMaster(RenderUtil * utils, PointerBasicShader shader) : shader(shader), utils(utils){}
};


#endif //GRAPHICSPROJECT_SKYMASTER_H
