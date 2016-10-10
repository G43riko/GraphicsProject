//
// Created by gabriel on 23.9.2016.
//

#include "Renderer.h"

Renderer::Renderer(PointerBasicShader shader){
    actualCamera = new Camera();
    shader -> bind();
    shader -> updateUniform("projectionMatrix", actualCamera -> getProjectionMatrix());
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

void Renderer::render(PointerEntity entity, PointerBasicShader shader){
    shader -> bind();

    actualCamera -> input();
    shader -> updateUniform("viewMatrix", actualCamera -> getViewMatrix());


    shader -> updateUniform("lightPosition", light -> position);
    shader -> updateUniform("lightColor", light -> color);

    PointerRawModel model = entity -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform("transformationMatrix", Maths::createTransformationMatrix(entity -> getTransform()));
    prepareMaterial(entity -> getModel() -> getMaterial());
    prepareModel(model, 3);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    finishRender(3);
}

void Renderer::prepare(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1){
    glEnable(GL_DEPTH_TEST);
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