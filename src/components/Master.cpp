//
// Created by gabriel on 10.1.2017.
//

#include "Master.h"

void Master::updateProjectionMatrix(const BasicCamera& camera) {
    if (waterMaster) {
        RenderUtil::updateProjectionMatrix(waterMaster -> getShader(), camera);
    };
    if (skyBoxMaster) {
        RenderUtil::updateProjectionMatrix(skyBoxMaster -> getShader(), camera);
    };
    if (entityMaster) {
        RenderUtil::updateProjectionMatrix(*entityMaster -> getShader(), camera);
    };
    if (guiMaster) {
        RenderUtil::updateProjectionMatrix(guiMaster -> getShader(), camera);
    };
    if (voxelMaster) {
        RenderUtil::updateProjectionMatrix(voxelMaster -> getShader(), camera);
    };
}

void Master::init(Loader loader, int width, int height, BasicCamera& camera, PointerBasicShader shadowShader){
    shadowMaster = new ShadowMaster(shadowShader, camera);
    if (options.useGuis) {
        guiMaster = new GuiMaster(loader);
    };
    if (options.useSkybox) {
        skyBoxMaster = new SkyBoxMaster(camera, loader);
    };
    if (options.useParticles) {
        particleMaster = new ParticleMaster(camera, loader);
    };
    if (options.useEntities) {
        entityMaster = new EntityMaster(camera);
    };
    if (options.useWaters) {
        waterMaster = new WaterMaster(camera, loader);
    };
    voxelMaster = new VoxelMaster(camera, nullptr);
    postFxMaster = new PostFxMaster(loader, false, width, height);
    postFxMaster -> addFbo("fbo1", width, height, FBO_DEPTH_TEXTURE);
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
