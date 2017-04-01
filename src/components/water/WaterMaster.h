//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_WATERMASTER_H
#define GRAPHICSPROJECT_WATERMASTER_H


#include <src/rendering/RenderUtil.h>
#include "WaterTile.h"
#include <src/rendering/shader/WaterShader.cpp>
#include <src/rendering/material/TextureManager.h>
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
    PointerTexture2D dudvMap = TextureManager::createTexture2D("res/textures/waterDUDV.png");
    PointerTexture2D normalMap = TextureManager::createTexture2D("res/textures/matchingNormalMap.png");

    BasicShader * shader = new WaterShader();
    float distance;
public:
    void render(PointerCamera camera, std::vector<PointerPointLight> lights);
    WaterMaster(PointerCamera camera, Loader loader){
        std::vector<float> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
        quad = loader.loadToVao(vertices, 2);
        RenderUtil::updateProjectionMatrix(shader, camera);
    };


    void update(float delta){
        moveFactor += waterSpeed * delta;
    };
    void cleanUp(void){
        shader -> cleanUp();
        delete shader;
    };

    void starRenderReflection(PointerCamera camera){
        fbo.bindReflectionFrameBuffer();
        distance = 2 * (camera -> position.y - water.getHeight());
        camera -> position.y -= distance;
        camera -> pitch *= -1;
    };
    void starRenderRefraction(PointerCamera camera){
        camera -> pitch *= -1;
        camera -> position.y += distance;
        fbo.bindRefractionFrameBuffer();
    };
    void finishRender(void){
        fbo.unbindCurrentFrameBuffer();
    };
    /******************GETTERS******************/
    BasicShader * getShader(void){
        return shader;
    };
    float getTilig(void){
        return tiling;
    };
    float getWaveStrenght(void){
        return waveStrength;
    };
    float getShineDumper(void){
        return tiling;
    };
    float getReflectivity(void){
        return reflectivity;
    };
    float getWaterSpeed(void){
        return waterSpeed;
    };
    float getRefractiveRation(void){
        return refractiveRation;
    };
    float getWaterHeight(void){
        return water.getHeight();
    };
    /******************SETTER******************/
    void setWaterHeight(float height){
        water.setHeight(height);
    }
    void setTiling(float tiling){
        this -> tiling = tiling;
    };
    void setWaveStrength(float waveStrength){
        this -> waveStrength = waveStrength;
    };
    void setShineDumper(float shineDumper){
        this -> shineDumper = shineDumper;
    };
    void setReflectivity(float reflectivity){
        this -> reflectivity = reflectivity;
    };
    void setWaterSpeed(float waterSpeed){
        this -> waterSpeed = waterSpeed;
    };
    void setRefractiveRation(float refractiveRation){
        this -> refractiveRation = refractiveRation;
    };
};


#endif //GRAPHICSPROJECT_WATERMASTER_H
