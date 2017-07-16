//
// Created by gabriel on 6.1.2017.
//

#ifndef GRAPHICSPROJECT_SHADOWMASTER_H
#define GRAPHICSPROJECT_SHADOWMASTER_H


#include <src/components/entities/EntityManager.h>
#include <src/components/postProccessing/Fbo.h>
#include <src/rendering/RenderUtil.h>
#include "ShadowBox.h"
#include "ShadowFrameBuffer.h"
class ShadowMaster {
private:
    PointerBasicShader shader;
//    Fbo fbo = Fbo(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
    ShadowFrameBuffer fbo = ShadowFrameBuffer(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
    ShadowBox box;

    Matrix4f projectionMatrix;
    Matrix4f lightViewMatrix;
    Matrix4f projectionViewMatrix;
    Matrix4f offset = createOffset();

    Matrix4f createOffset(void);
    Matrix4f updateLightViewMatrix(Vector3f direction, Vector3f center);
    void prepare(Vector3f lightPosition, ShadowBox box);
    Matrix4f updateOrthoProjectionMatrix(float width, float height, float length);
    //void finish();
public:
//    ShadowMaster(PointerBasicShader shader, PointerCamera camera) : shader(shader), box(ShadowBox(&lightViewMatrix, camera)){};
    ShadowMaster(PointerBasicShader shader, BasicCamera& camera) : shader(shader), box(ShadowBox(&lightViewMatrix, camera)){};
    void cleanUp(void){};
    void renderShadows(EntitiesList entities, PointerPointLight sun, PointerCamera camera);
    void renderShadows(std::vector<PointerEntity> entities, PointerPointLight sun, PointerCamera camera);
    void renderShadow(PointerEntity entity, PointerPointLight sun, PointerCamera camera);

    Matrix4f getToShadowMapSpaceMatrix(void);
    GLuint getShadowMap(void);
};

#endif //GRAPHICSPROJECT_SHADOWMASTER_H
