//
// Created by gabriel on 6.1.2017.
//

#include "ShadowMaster.h"

void ShadowMaster::renderShadows(EntitiesList entities, PointerPointLight sun, PointerCamera camera){
    if(entities.empty() || !sun){
        return;
    }
    shader -> bind();
    glEnableVertexAttribArray(0);

    fbo.bindFrameBuffer();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);



    box.update();
    prepare(sun -> getPosition() * -1, box);
    if(Input::getKeyDown(GLFW_KEY_L)){
        camera ->position.show();
    }

    //shader -> updateUniform4m("mvpMatrix", projectionViewMatrix);

    for (auto it = entities.begin(); it != entities.end(); ++it){ //pre všetky materialy
        if(it -> second.size()){
            auto itEnt = it->second.begin();

            while(itEnt != it->second.end()){ //prejde všetky entity
                glBindVertexArray(itEnt ->get() -> getModel() -> getModel() -> getVaoID());
                shader -> updateUniform4m("mpvMatrix", projectionViewMatrix * itEnt -> get() -> getTransform() -> getTransformation());
                glDrawElements(GL_TRIANGLES, itEnt ->get() -> getModel() -> getModel() -> getVertexCount(), GL_UNSIGNED_INT, 0);
                itEnt++;
            }
        }
    }
    fbo.unbindFrameBuffer();
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void ShadowMaster::renderShadows(std::vector<PointerEntity> entities, PointerPointLight sun, PointerCamera camera){
    if(entities.empty() || !sun){
        return;
    }
    shader -> bind();
    glEnableVertexAttribArray(0);

    fbo.bindFrameBuffer();
    //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);


    box.update();
    prepare(sun -> getPosition() , box);

    shader -> updateUniform4m("mvpMatrix", projectionViewMatrix);

    for(PointerEntity entity : entities){
        glBindVertexArray(entity -> getModel() -> getModel() -> getVaoID());
        Matrix4f modelMatrix = entity -> getTransform() -> getTransformation();
        shader -> updateUniform4m("mpvMatrix", Matrix4f(camera -> getProjectionMatrix()) * Matrix4f(camera -> getViewMatrix()) * modelMatrix);

        glDrawElements(GL_TRIANGLES, entity -> getModel() -> getModel() -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }

    fbo.unbindFrameBuffer();
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void ShadowMaster::renderShadow(PointerEntity entity, PointerPointLight sun, PointerCamera camera){
    if(!sun){
        return;
    }
    shader -> bind();


    //prepareMaterial(entity -> getModel() -> getMaterial(), shader);

    glBindVertexArray(entity -> getModel() -> getModel() -> getVaoID());
    glEnableVertexAttribArray(0);
    box.update();
    prepare(sun -> getPosition() * -1, box);

    Matrix4f modelMatrix = entity -> getTransform() -> getTransformation();
    shader -> updateUniform4m("mpvMatrix", Matrix4f(camera -> getProjectionMatrix()) * Matrix4f(camera -> getViewMatrix()) * modelMatrix);

    glDrawElements(GL_TRIANGLES, entity -> getModel() -> getModel() -> getVertexCount(), GL_UNSIGNED_INT, 0);

    fbo.unbindFrameBuffer();
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

Matrix4f ShadowMaster::createOffset(void){
    /*
    Matrix4f offset = Matrix4f();
    Matrix4f::translate(Vector3f(0.5f, 0.5f, 0.5f), offset, &offset);
    */
    Matrix4f offset = Matrix4f::initTranslation(0.5f, 0.5f, 0.5f);
     Matrix4f::scale(Vector3f(0.5f, 0.5f, 0.5f), offset, &offset);
    return offset;
}
Matrix4f ShadowMaster::updateLightViewMatrix(Vector3f direction, Vector3f center) {
    direction.normalize();
    center *= -1;
    Matrix4f::setIdentity(lightViewMatrix);
    float pitch = (float) acos(Vector2f(direction.x, direction.z).length());
    Matrix4f::rotate(pitch, Vector3f(1, 0, 0), lightViewMatrix, &lightViewMatrix);
    float yaw = (float) (TO_DEGREES(((float) atan(direction.x / direction.z))));
    yaw = direction.z > 0 ? yaw - 180 : yaw;
//    lightViewMatrix *= Matrix4f::initRotation(0, -yaw, 0);

    Matrix4f::rotate(-(float)(TO_RADIANS(yaw)), Vector3f(0, 1, 0), lightViewMatrix, &lightViewMatrix);
    Matrix4f::translate(center, lightViewMatrix, &lightViewMatrix);

    return lightViewMatrix;
}
//Matrix4f ShadowMaster::updateLightViewMatrix(Vector3f direction, Vector3f center) {
//    printf("DIR: \n");
//    direction.show();
//    printf("CENTER: \n");
//    center.show();
//    direction.normalize();
//    center *= -1;
//    float pitch = (float)acos(Vector2f(direction.x, direction.z).length());
//    float yaw = (float)(TO_DEGREES(atan(direction.x / direction.z)));
//    yaw = direction.z > 0 ? yaw - 180 : yaw;
//    //return Matrix4f::initTranslation(center.x, center.y, center.z) * Matrix4f::initRotation(0, -(float)(TO_RADIANS(yaw)), 0) * result;
//    Matrix4f result = Matrix4f::initTranslation(center.x, center.y, center.z) * Matrix4f::initRotation(0, -(yaw), 0) * Matrix4f::initRotation(pitch, 0, 0);
//    printf("RESULT: \n");
//    result.show();
//
//    return result;
//}

void ShadowMaster::prepare(Vector3f lightPosition, ShadowBox box) {
    projectionMatrix = updateOrthoProjectionMatrix(box.getWidth(), box.getHeight(), box.getLength());
    lightViewMatrix = updateLightViewMatrix(lightPosition, box.getCenter());

    projectionViewMatrix = projectionMatrix * lightViewMatrix;
}

Matrix4f ShadowMaster::updateOrthoProjectionMatrix(float width, float height, float length) {
    Matrix4f result;
    result.m00 = 2.0f / width;
    result.m11 = 2.0f / height;
    result.m22 = -2.0f / length;
    result.m33 = 1;
    return result;
}
/*
void ShadowMaster::render(PointerEntity entitie, PointerPointLight sun){
    box.update();
    prepare(sun -> getPosition() * -1, box);
}
*/

Matrix4f ShadowMaster::getToShadowMapSpaceMatrix(void){
    return offset * projectionViewMatrix;
}

GLuint ShadowMaster::getShadowMap() {
    //return fbo.getDepthBuffer();
//    return fbo.getColourTexture();
//    return fbo.getDepthTexture();
    return fbo.getShadowMap();
}