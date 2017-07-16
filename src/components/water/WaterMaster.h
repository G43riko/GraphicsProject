//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_WATERMASTER_H
#define GRAPHICSPROJECT_WATERMASTER_H


#include <src/rendering/RenderUtil.h>
#include <src/rendering/shader/WaterShader.h>
#include <src/rendering/material/TextureManager.h>
#include "WaterFrameBuffer.h"
#include "WaterTile.h"


class WaterMaster {
    float tiling            = 6.0;
    float waveStrength      = 0.02f;
    float shineDumper       = 20.0f;
    float reflectivity      = 0.6f;
    float refractiveRation  = 1.0f;
    float waterSpeed        = 0.001f;
    float moveFactor        = 0;
    const PointerRawModel quad;
    WaterFrameBuffer fbo    = WaterFrameBuffer();
    WaterTile water         = WaterTile(0, 0, DEFAULT_WATER_HEIGHT, DEFAULT_WATER_SIZE);
    std::vector<WaterTile *> waters;
    PointerTexture2D dudvMap = TextureManager::instance.createTexture2D("res/textures/waterDUDV.png");
    PointerTexture2D normalMap = TextureManager::instance.createTexture2D("res/textures/matchingNormalMap.png");

    WaterShader shader = WaterShader();
    float distance;
public:
    inline WaterMaster(BasicCamera& camera, Loader loader) : quad(loader.loadToVao(WATER_VERTICES, 2)){
        RenderUtil::updateProjectionMatrix(shader, camera);
    };
    inline void addWater(float centerX,
                         float centerZ,
                         float height = DEFAULT_WATER_HEIGHT,
                         float size = DEFAULT_WATER_SIZE){
        waters.push_back(new WaterTile(centerX, centerZ, height, size));
    }
    void render(PointerCamera camera, std::vector<PointerPointLight> lights);


    inline void update(float delta){
        moveFactor += waterSpeed * delta;
    };
    inline void cleanUp(void){
        shader.cleanUp();
        ITERATE_VECTOR(waters, i){
            delete waters[i];
        }
        waters.clear();
    };

    inline void starRenderReflection(PointerCamera camera){
        fbo.bindReflectionFrameBuffer();
        distance = 2 * (camera -> getPosition().y - water.getHeight());
        camera -> getTransform() -> move(0, -distance, 0);
        camera -> getTransform() -> getRotation().x = -camera -> getTransform() -> getRotation(). x;
        camera -> getTransform() -> getRotation().z = -camera -> getTransform() -> getRotation().z;
    };
    inline void starRenderRefraction(PointerCamera camera) const{
        camera -> getTransform() -> getRotation().x = -camera -> getTransform() -> getRotation().x;
        camera -> getTransform() -> getRotation().z = -camera -> getTransform() -> getRotation().z;
        camera -> getTransform() -> move(0, distance, 0);
        fbo.bindRefractionFrameBuffer();
    };
    inline void finishRender(void) const{
        fbo.unbindCurrentFrameBuffer();
    };
    /******************GETTERS******************/
    inline float getTilig(void){ return tiling; };
    inline float getShineDumper(void){ return tiling; };
    inline BasicShader& getShader(void){ return shader; };
    inline float getWaterSpeed(void){ return waterSpeed; };
    inline float getWaveStrenght(void){ return waveStrength; };
    inline float getReflectivity(void){ return reflectivity; };
    inline float getWaterHeight(void){ return water.getHeight(); };
    inline float getRefractiveRation(void){ return refractiveRation; };
    /******************SETTER******************/
    inline void setTiling(float tiling){this -> tiling = tiling; };
    inline void setWaterHeight(float height){water.setHeight(height);}
    inline void setWaterSpeed(float waterSpeed){ this -> waterSpeed = waterSpeed; };
    inline void setShineDumper(float shineDumper){ this -> shineDumper = shineDumper;};
    inline void setWaveStrength(float waveStrength){ this -> waveStrength = waveStrength; };
    inline void setReflectivity(float reflectivity){ this -> reflectivity = reflectivity; };
    inline void setRefractiveRation(float refractiveRation){ this -> refractiveRation = refractiveRation; };
};


#endif //GRAPHICSPROJECT_WATERMASTER_H
