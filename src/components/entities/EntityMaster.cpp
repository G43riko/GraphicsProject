//
// Created by gabriel on 7.1.2017.
//

#include <src/rendering/Camera.h>
#include "EntityMaster.h"

void EntityMaster::renderEntities(std::vector<PointerEntity> entities, std::vector<PointerLight> lights, PointerCamera camera, int options, Vector4f clipPlane){
    if(entities.empty()){
        return;
    }
    shader -> bind();

    shader -> updateUniform4m("viewMatrix", camera -> getViewMatrix());
    shader -> updateUniform3f("cameraPosition", camera -> position);
    //shader -> updateUniform2f("levels", 4);
    shader -> updateUniform4f("plane", clipPlane);
    for(unsigned int i=0 ; i<lights.size() ; i++){
        utils -> updateLightUniforms(lights[i], shader, camera, i, false);
    }

    for(PointerEntity entity : entities){
        PointerRawModel model = entity -> getModel() -> getModel();
        glEnable(GL_TEXTURE);

        shader -> updateUniform4m("transformationMatrix", entity -> getTransform() -> getTransformation());

        utils -> prepareMaterial(entity -> getModel() -> getMaterial(), shader, options);
        utils -> prepareModel(model, 3);

        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }
    utils -> finishRender(3);
}
void EntityMaster::renderEntity(PointerEntity entity, std::vector<PointerLight> lights, PointerCamera camera, int options, Vector4f clipPlane){
    shader -> bind();

    shader -> updateUniform4m("viewMatrix", camera -> getViewMatrix());
    shader -> updateUniform3f("cameraPosition", camera -> position);
    //shader -> updateUniform2f("levels", 4);

    for(unsigned int i=0 ; i<lights.size() ; i++){
        utils -> updateLightUniforms(lights[i], shader, camera, i, false);
    }

    PointerRawModel model = entity -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m("transformationMatrix", entity -> getTransform() -> getTransformation());

    utils -> prepareMaterial(entity -> getModel() -> getMaterial(), shader, options);
    utils -> prepareModel(model, 3);

    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);

    utils -> finishRender(3);
}