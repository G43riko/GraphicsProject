//
// Created by gabriel on 6.1.2017.
//

#ifndef GRAPHICSPROJECT_SHADOWMASTER_H
#define GRAPHICSPROJECT_SHADOWMASTER_H


#include "../../rendering/RenderUtil.h"
#include <src/components/postProccessing/Fbo.h>
#include "ShadowBox.h"
#include "ShadowFrameBuffer.h"

class ShadowMaster {
private:
    PointerBasicShader shader;
    RenderUtil * utils;
    static constexpr int SHADOW_MAP_SIZE = 2048;
    Fbo fbo = Fbo(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
//    ShadowFrameBuffer fbo = ShadowFrameBuffer(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
    ShadowBox box;

    Matrix4f projectionMatrix;
    Matrix4f lightViewMatrix;
    Matrix4f projectionViewMatrix;
    Matrix4f offset = createOffset();

    Matrix4f createOffset(void);
    Matrix4f updateLightViewMatrix(Vector3f direction, Vector3f center);
    void prepare(Vector3f lightPosition, ShadowBox box);
    Matrix4f updateOrthoProjectionMatrix(float width, float height, float length);
    void finish();
public:
    ShadowMaster(RenderUtil * utils, PointerBasicShader shader, PointerCamera camera) : shader(shader), utils(utils), box(ShadowBox(&lightViewMatrix, camera)){}
    void renderShadows(std::vector<PointerEntity> entities, PointerLight sun, PointerCamera camera);
    void renderShadow(PointerEntity entity, PointerLight sun, PointerCamera camera);

    Matrix4f getToShadowMapSpaceMatrix(void);
    int getShadowMap(void);
};

#endif //GRAPHICSPROJECT_SHADOWMASTER_H
