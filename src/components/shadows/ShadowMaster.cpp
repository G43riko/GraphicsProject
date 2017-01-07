//
// Created by gabriel on 6.1.2017.
//

#include "ShadowMaster.h"

void ShadowMaster::renderShadows(std::vector<PointerEntity> entities, PointerLight sun, PointerCamera camera){
    if(entities.empty() || !sun){
        return;
    }

    shader -> bind();
    glEnableVertexAttribArray(0);
    for(PointerEntity entity : entities){
        render(entity, sun);
        glBindVertexArray(entity -> getModel() -> getModel() -> getVaoID());
        Matrix4f modelMatrix = entity -> getTransform() -> getTransformation();
        shader -> updateUniform4m("mpvMatrix", Matrix4f(camera -> getProjectionMatrix()) * Matrix4f(camera -> getViewMatrix()) * modelMatrix);

        glDrawElements(GL_TRIANGLES, entity -> getModel() -> getModel() -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }

    finish();
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void ShadowMaster::renderShadow(PointerEntity entity, PointerLight sun, PointerCamera camera){
    if(!sun){
        return;
    }
    render(entity, sun);
    shader -> bind();

    //prepareMaterial(entity -> getModel() -> getMaterial(), shader);

    glBindVertexArray(entity -> getModel() -> getModel() -> getVaoID());
    glEnableVertexAttribArray(0);

    Matrix4f modelMatrix = entity -> getTransform() -> getTransformation();
    shader -> updateUniform4m("mpvMatrix", Matrix4f(camera -> getProjectionMatrix()) * Matrix4f(camera -> getViewMatrix()) * modelMatrix);

    glDrawElements(GL_TRIANGLES, entity -> getModel() -> getModel() -> getVertexCount(), GL_UNSIGNED_INT, 0);

    finish();
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

Matrix4f ShadowMaster::createOffset(void){
    Matrix4f offset = Matrix4f();
    Matrix4f::translate(Vector3f(0.5f, 0.5f, 0.5f), offset, &offset);
    Matrix4f::scale(Vector3f(0.5f, 0.5f, 0.5f), offset, &offset);
    return offset;
}

Matrix4f ShadowMaster::updateLightViewMatrix(Vector3f direction, Vector3f center) {
    direction.normalize();
    center *= -1;
    Matrix4f result;
    float pitch = (float) acos(Vector2f(direction.x, direction.z).length());
    Matrix4f::rotate(pitch, Vector3f(1, 0, 0), result, &result);
    float yaw = (float) TO_DEGREES(((float) atan(direction.x / direction.z)));
    yaw = direction.z > 0 ? yaw - 180 : yaw;
    Matrix4f::rotate((float) -TO_RADIANS(yaw), Vector3f(0, 1, 0), result, &result);
    Matrix4f::translate(center, result, &result);
    return result;
}

void ShadowMaster::prepare(Vector3f lightDirection, ShadowBox box) {
    projectionMatrix = updateOrthoProjectionMatrix(box.getWidth(), box.getHeight(), box.getLength());
    lightViewMatrix = updateLightViewMatrix(lightDirection, box.getCenter());
    projectionViewMatrix = projectionMatrix * lightViewMatrix;
    fbo.bindFrameBuffer();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
}

Matrix4f ShadowMaster::updateOrthoProjectionMatrix(float width, float height, float length) {
    Matrix4f result;
    result.m00 = 2.0f / width;
    result.m11 = 2.0f / height;
    result.m22 = -2.0f / length;
    result.m33 = 1;
    return result;
}

void ShadowMaster::render(PointerEntity entitie, PointerLight sun){
    box.update();
    prepare(sun -> getPosition() * -1, box);
}

void ShadowMaster::finish() {
    fbo.unbindFrameBuffer();
}

Matrix4f ShadowMaster::getToShadowMapSpaceMatrix(void){
    return offset * projectionViewMatrix;
}
int ShadowMaster::getShadowMap() {
    return fbo.getDepthBuffer();
    //return fbo.getColourTexture();
}