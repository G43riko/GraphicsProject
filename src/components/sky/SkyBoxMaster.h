//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_SKYMASTER_H
#define GRAPHICSPROJECT_SKYMASTER_H

#include <src/rendering/material/CubeTexture.h>
#include <src/rendering/RenderUtil.h>

class SkyBoxMaster {
private:
    constexpr static float SIZE = 500;
    PointerBasicShader shader;
    RenderUtil * utils;
    PointerRawModel model;
public:
    void renderSky(CubeTexture sky, PointerCamera camera);
    SkyBoxMaster(RenderUtil * utils, PointerBasicShader shader, Loader loader) : shader(shader), utils(utils){
        std::vector<float> vertices = {
            -SIZE,  SIZE, -SIZE,
            -SIZE, -SIZE, -SIZE,
             SIZE, -SIZE, -SIZE,
             SIZE, -SIZE, -SIZE,
             SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,

            -SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,

             SIZE, -SIZE, -SIZE,
             SIZE, -SIZE,  SIZE,
             SIZE,  SIZE,  SIZE,
             SIZE,  SIZE,  SIZE,
             SIZE,  SIZE, -SIZE,
             SIZE, -SIZE, -SIZE,

            -SIZE, -SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
             SIZE,  SIZE,  SIZE,
             SIZE,  SIZE,  SIZE,
             SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,

            -SIZE,  SIZE, -SIZE,
             SIZE,  SIZE, -SIZE,
             SIZE,  SIZE,  SIZE,
             SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE, -SIZE,

            -SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
             SIZE, -SIZE, -SIZE,
             SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
             SIZE, -SIZE,  SIZE
        };
        model = loader.loadToVao(vertices, 3);
    }
};


#endif //GRAPHICSPROJECT_SKYMASTER_H
