//
// Created by gabriel on 23.9.2016.
//

#include "Renderer.h"

void Renderer::setCamera(PointerCamera camera){
    actualCamera = camera;
    updateProjectionMatrix(camera);
}

void Renderer::updateProjectionMatrix(PointerCamera camera, PointerBasicShader shader){
    if(shader){
        shader -> bind();
        shader -> updateUniform4m("projectionMatrix", camera -> getProjectionMatrix());
    }
    else {
        for (auto it = shaders.begin(); it != shaders.end(); ++it){
            if (it->second->hasUniform("projectionMatrix")) {
                it->second->bind();
                it->second->updateUniform4m("projectionMatrix", camera->getProjectionMatrix());
            }
        }
    }
}

void Renderer::addShader(std::string key, PointerBasicShader shader){
    shaders[key] = shader;
    if(actualCamera)
        updateProjectionMatrix(actualCamera, shader);
}

void Renderer::init3D(){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::render(PointerRawModel model){
    prepareModel(model, 0);
    //glDrawArrays(GL_TRIANGLES, 0, model -> getVertexCount());// - pri použíťí index baferu sa nepoužíva
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    finishRender(0);
}
void Renderer::render(PointerMaterialedModel materialedModel){
    PointerRawModel model = materialedModel -> getModel();
    glEnable(GL_TEXTURE);
    prepareMaterial(materialedModel -> getMaterial());
    prepareModel(model, 1);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    finishRender(1);
}
void Renderer::renderObject(PointerEntity object, std::vector<PointerLight> lights){
    PointerBasicShader shader = shaders["objectShader"];
    if(!shader)
        return;
    shader -> bind();

    actualCamera -> input();
    shader -> updateUniform4m("viewMatrix", actualCamera -> getViewMatrix());
    //shader -> updateUniform("levels", 4);

    for(int i=0 ; i<lights.size() ; i++){
        shader -> updateUniform("lightPosition[" + std::to_string(i) + "]", lights.at(i) -> position);
        shader -> updateUniform("lightColor[" + std::to_string(i) + "]", lights.at(i) -> color);
    }

    PointerRawModel model = object -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m("transformationMatrix", Maths::createTransformationMatrix(object -> getTransform()));
    prepareMaterial(object -> getModel() -> getMaterial());
    prepareModel(model, 4);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    finishRender(4);
}
void Renderer::renderEntity(PointerEntity entity){
    PointerBasicShader shader = shaders["entityShader"];
    if(!shader)
        return;
    shader -> bind();

    actualCamera -> input();
    shader -> updateUniform4m("viewMatrix", actualCamera -> getViewMatrix());
    //shader -> updateUniform("levels", 4);

    shader -> updateUniform("lightPosition", light -> position);
    shader -> updateUniform("lightColor", light -> color);

    PointerRawModel model = entity -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m("transformationMatrix", Maths::createTransformationMatrix(entity -> getTransform()));
    prepareMaterial(entity -> getModel() -> getMaterial());
    prepareModel(model, 3);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    finishRender(3);
}

void Renderer::renderScreen(Screen * screen, int texture) {
    PointerBasicShader shader = shaders["postFxShader"];
    if(!shader)
        return;
    shader -> bind();
    glBindVertexArray(screen -> getModel() -> getVaoID());
    glEnableVertexAttribArray(0);

    glDisable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    screen -> getTexture() -> bind();
    if(texture > 0)
        glBindTexture(GL_TEXTURE_2D, texture);

    shader -> updateUniform4m("transformationMatrix", screen -> getTransformationMatrix());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, screen -> getModel() -> getVertexCount());

    glEnable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::prepare(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1){
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::prepareModel(PointerRawModel model, GLuint numberOfAttributes){
    glBindVertexArray(model -> getVaoID());
    for(GLuint i=0 ; i<=numberOfAttributes ; i++)
        glEnableVertexAttribArray(i);
}
void Renderer::prepareMaterial(PointerMaterial material){
    material -> getDiffuse() -> bind(GL_TEXTURE0);
}

void Renderer::finishRender(GLuint numberOfAttributes){
    for(GLuint i=0 ; i<=numberOfAttributes ; i++)
        glDisableVertexAttribArray(i);

    glBindVertexArray(0);

}