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
    float const waterSpeed = 0.0003f;
    float moveFactor = 0;
    PointerRawModel quad;
    WaterTile water = WaterTile(0, 0, 1.5f);
    PointerTexture2D dudvMap = ContentLoader::loadTexturePNG("res/textures/waterDUDV.png");
    PointerTexture2D normalMap = ContentLoader::loadTexturePNG("res/textures/matchingNormalMap.png");

    PointerBasicShader shader;
    RenderUtil * utils;
public:
    //void renderWater(CubeTexture sky, PointerRawModel model, PointerCamera camera);
    void render(PointerCamera camera, std::vector<PointerLight> lights, WaterFrameBuffer fbos);
    WaterMaster(RenderUtil * utils, PointerBasicShader shader, Loader loader) : shader(shader), utils(utils){
        std::vector<float> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
        quad = loader.loadToVao(vertices, 2);
    }
    float getWaterHeight(void){
        return water.getHeight();
    }
};


#endif //GRAPHICSPROJECT_WATERMASTER_H
