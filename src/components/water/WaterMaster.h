//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_WATERMASTER_H
#define GRAPHICSPROJECT_WATERMASTER_H


#include <src/rendering/RenderUtil.h>
#include "WaterTile.h"
#include "WaterFrameBuffer.h"

class WaterMaster {
private:
    float tiling = 6.0;
    float waveStrength = 0.02f;
    float shineDumper = 20.0f;
    float reflectivity = 0.6f;
    float refractiveRation = 1.0f;
    float waterSpeed = 0.001f;
    float moveFactor = 0;
    PointerRawModel quad;
    WaterFrameBuffer fbo = WaterFrameBuffer();
    WaterTile water = WaterTile(0, 0, 1.5f);
    PointerTexture2D dudvMap = ContentLoader::loadTexturePNG("res/textures/waterDUDV.png");
    PointerTexture2D normalMap = ContentLoader::loadTexturePNG("res/textures/matchingNormalMap.png");

    PointerBasicShader shader;
    RenderUtil * utils;
    float distance;
public:
    void render(PointerCamera camera, std::vector<PointerLight> lights);
    WaterMaster(RenderUtil * utils, PointerBasicShader shader, Loader loader) : shader(shader), utils(utils){
        std::vector<float> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
        quad = loader.loadToVao(vertices, 2);
    }
    void update(float delta){
        moveFactor += waterSpeed * delta;
    }

    float getWaterHeight(void){
        return water.getHeight();
    }

    void starRenderReflection(PointerCamera camera){
        fbo.bindReflectionFrameBuffer();
        distance = 2 * (camera -> position.y - water.getHeight());
        camera -> position.y -= distance;
        camera -> pitch *= -1;
    }
    void starRenderRefraction(PointerCamera camera){
        camera -> pitch *= -1;
        camera -> position.y += distance;
        fbo.bindRefractionFrameBuffer();
    }
    void finishRender(void){
        fbo.unbindCurrentFrameBuffer();
    }
};


#endif //GRAPHICSPROJECT_WATERMASTER_H
