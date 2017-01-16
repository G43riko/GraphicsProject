//
// Created by gabriel on 16.1.2017.
//

#ifndef GRAPHICSPROJECT_RENDERERINTERFACE_H
#define GRAPHICSPROJECT_RENDERERINTERFACE_H

#include <src/components/water/WaterMaster.h>
#include <src/components/entities/EntityMaster.h>
#include <src/components/particles/ParticleMaster.h>
#include <src/components/gui/GuiMaster.h>
#include <src/components/sky/SkyBoxMaster.h>
#include <src/components/postProccessing/PostFxMaster.h>
#include <src/components/shadows/ShadowMaster.h>

class RenderInterface{
private:
    Loader * loader;

    WaterMaster * waterMaster = nullptr;
    EntityMaster * entityMaster = nullptr;
    ParticleMaster * particleMaster = nullptr;
    GuiMaster * guiMaster = nullptr;
    SkyBoxMaster * skyBoxMaster = nullptr;
    PostFxMaster * postFxMaster = nullptr;
    ShadowMaster * shadowMaster = nullptr;

    bool useShadow = false;
    bool useParticle = true;
    bool useSkybox = true;
    bool useWater = true;
    bool usePostFx = false;
    bool useGui = true;
    bool useTexture = false;
    bool useNormal = false;
    bool useLight = false;
    bool useSpecular = false;
    bool useEnviromental = false;
public:
    WaterMaster * getWaterMaster(void){

    }


/**************************************************GETTERS**************************************************/
bool isUseShadows(){
    return useShadow;
}

void setShadows(bool useShadows) {
    this -> useShadow = useShadows;
}

bool useParticles(){
    return useParticle;
}

void setParticles(bool useParticles) {
    this -> useParticle = useParticles;
}

bool useSkyboxes(){
    return useSkybox;
}

void setSkybox(bool useSkybox) {
    this -> useSkybox = useSkybox;
}

bool useWaters(){
    return useWater;
}

void setWaters(bool useWater) {
    this -> useWater = useWater;
}

bool usePostFxs(){
    return usePostFx;
}

void setPostFx(bool usePostFx) {
    this -> usePostFx = usePostFx;
}

bool useGuis() const {
    return useGui;
}

void setGuis(bool useGui) {
    this -> useGui = useGui;
}

bool useTextures() const {
    return useTexture;
}

void setUseTextures(bool useTexture) {
    this -> useTexture = useTexture;
}

bool useNormals(){
    return useNormal;
}

void setUseNormals(bool useNormal) {
    this -> useNormal = useNormal;
}

bool useLights(){
    return useLight;
}

void setUseLights(bool useLight) {
    this -> useLight = useLight;
}

bool useSpeculars(){
    return useSpecular;
}

void setUseSpeculars(bool useSpecular) {
    this -> useSpecular = useSpecular;
}

bool useEnviromentals(){
    return useEnviromental;
}

void setUseEnviromentals(bool useEnviromental) {
    this -> useEnviromental = useEnviromental;
}
};

#endif //GRAPHICSPROJECT_RENDERERINTERFACE_H
