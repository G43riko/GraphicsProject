//
// Created by gabriel on 6.1.2017.
//

#ifndef GRAPHICSPROJECT_SHADOWMASTER_H
#define GRAPHICSPROJECT_SHADOWMASTER_H


#include <src/components/postProccessing/Fbo.h>
#include <src/entities/Light.h>
#include <src/rendering/model/Entity.h>
#include "ShadowBox.h"

class ShadowMaster {
private:
    static constexpr int SHADOW_MAP_SIZE = 2048;
    Fbo fbo = Fbo(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
    ShadowBox box;

    Matrix4f projectionMatrix;
    Matrix4f lightViewMatrix;
    Matrix4f projectionViewMatrix;
    Matrix4f offset = createOffset();

    Matrix4f createOffset(void){
        Matrix4f offset = Matrix4f();
        Matrix4f::translate(Vector3f(0.5f, 0.5f, 0.5f), offset, &offset);
        Matrix4f::scale(Vector3f(0.5f, 0.5f, 0.5f), offset, &offset);
        return offset;
    }

    void updateLightViewMatrix(Vector3f direction, Vector3f center) {
        direction.normalize();
        center *= -1;
        Matrix4f::setIdentity(lightViewMatrix);
        float pitch = (float) acos(Vector2f(direction.x, direction.z).length());
        Matrix4f::rotate(pitch, Vector3f(1, 0, 0), lightViewMatrix, &lightViewMatrix);
        float yaw = (float) TO_DEGREES(((float) atan(direction.x / direction.z)));
        yaw = direction.z > 0 ? yaw - 180 : yaw;
        Matrix4f::rotate((float) -TO_RADIANS(yaw), Vector3f(0, 1, 0), lightViewMatrix, &lightViewMatrix);
        Matrix4f::translate(center, lightViewMatrix, &lightViewMatrix);
    }

    void prepare(Vector3f lightDirection, ShadowBox box) {
        updateOrthoProjectionMatrix(box.getWidth(), box.getHeight(), box.getLength());
        updateLightViewMatrix(lightDirection, box.getCenter());
        projectionViewMatrix = projectionMatrix * lightViewMatrix;
        fbo.bindFrameBuffer();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void updateOrthoProjectionMatrix(float width, float height, float length) {
        Matrix4f::setIdentity(projectionMatrix);
        projectionMatrix.m00 = 2.0f / width;
        projectionMatrix.m11 = 2.0f / height;
        projectionMatrix.m22 = -2.0f / length;
        projectionMatrix.m33 = 1;
    }
public:
    ShadowMaster(PointerCamera camera) : box(ShadowBox(&lightViewMatrix, camera)){}
    void render(PointerEntity entitie, PointerLight sun){
        box.update();
        prepare(sun -> getPosition() * -1, box);
    }

    void finish() {
        fbo.unbindFrameBuffer();
    }

    Matrix4f getToShadowMapSpaceMatrix(void){
        return offset * projectionViewMatrix;
    }
    int getShadowMap() {
        //return fbo.getDepthBuffer();
        return fbo.getColourTexture();
    }
};

#endif //GRAPHICSPROJECT_SHADOWMASTER_H
