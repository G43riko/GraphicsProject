//
// Created by gabriel on 10.1.2017.
//

#include "Master.h"

Master::Master(void){
    initOptions();
}

void Master::initOptions(void) {
    options.useShadows = false;
    options.useEntities = true;
    options.useParticles = true;
    options.useSkybox = true;
    options.useWaters = true;
    options.usePostFx = false;
    options.useVoxels = true;
    options.useGuis = true;
    options.useTextures = false;
    options.useNormals = false;
    options.useLights = false;
    options.useSpeculars = false;
    options.useEnviromentals = false;
}

void Master::updateProjectionMatrix(PointerCamera camera) {
    if (waterMaster) {
        RenderUtil::updateProjectionMatrix(waterMaster -> getShader(), camera);
    };
    if (skyBoxMaster) {
        RenderUtil::updateProjectionMatrix(skyBoxMaster -> getShader(), camera);
    };
    if (voxelMaster) {
        RenderUtil::updateProjectionMatrix(voxelMaster -> getShader(), camera);
    };
    if (entityMaster) {
        RenderUtil::updateProjectionMatrix(entityMaster -> getShader(), camera);
    };
    if (guiMaster) {
        RenderUtil::updateProjectionMatrix(guiMaster -> getShader(), camera);
    };
    if (voxelMaster) {
        RenderUtil::updateProjectionMatrix(voxelMaster -> getShader(), camera);
    };
}

void Master::cleanUp(void) {
    CHECK_AND_CLEAR(shadowMaster);
    CHECK_AND_CLEAR(guiMaster);
    CHECK_AND_CLEAR(skyBoxMaster);
    CHECK_AND_CLEAR(entityMaster);
    CHECK_AND_CLEAR(particleMaster);
    CHECK_AND_CLEAR(postFxMaster);
    CHECK_AND_CLEAR(waterMaster);
    CHECK_AND_CLEAR(voxelMaster);
}

void Master::update(float delta){
    if(waterMaster){
        waterMaster -> update(delta);
    }
}

void Master::init(Loader loader, int width, int height, PointerCamera camera, PointerBasicShader shadowShader, PointerBasicShader particleShader) {
    shadowMaster = new ShadowMaster(shadowShader, camera);
    if (options.useGuis) {
        guiMaster = new GuiMaster(camera, loader);
    };
    if (options.useSkybox) {
        skyBoxMaster = new SkyBoxMaster(camera, loader);
    };
    if (options.useParticles) {
        particleMaster = new ParticleMaster(particleShader, loader);
    };
    if (options.useEntities) {
        entityMaster = new EntityMaster(camera);
    };
    if (options.useWaters) {
        waterMaster = new WaterMaster(camera, loader);
    };
    voxelMaster = new VoxelMaster();
    postFxMaster = new PostFxMaster(loader, false, width, height);
    postFxMaster->addFbo("fbo1", width, height, Fbo::DEPTH_TEXTURE);
}