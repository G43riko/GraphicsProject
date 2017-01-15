//
// Created by gabriel on 7.1.2017.
//

#include <src/rendering/Camera.h>
#include "EntityMaster.h"


void EntityMaster::renderEntities(EntitiesList entities, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane, Matrix4f toShadowSpace, GLuint shadowMap){
    if(entities.empty()){
        return;
    }
    shader -> bind();
    shader -> updateUniform4m("toShadowSpace", toShadowSpace);
    shader -> updateUniform4m("viewMatrix", camera -> getViewMatrix());
    shader -> updateUniform3f("cameraPosition", camera -> position);
    //shader -> updateUniform2f("levels", 4);
    shader -> updateUniform4f("plane", clipPlane);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    for(unsigned int i=0 ; i<lights.size() ; i++){
        utils -> updateLightUniforms(lights[i], shader, camera, i, false);
    }

    glEnable(GL_TEXTURE);
    for (auto it = entities.begin(); it != entities.end(); ++it){ //pre všetky materialy
        if(it -> second.size()){
            auto itEnt = it->second.begin();

            PointerRawModel model = it->first -> getModel();
            utils -> prepareModel(model, 3);
            utils -> prepareMaterial(it->first-> getMaterial(), shader, options);

            while(itEnt != it->second.end()){ //prejde všetky entity
                shader -> updateUniform4m("transformationMatrix", itEnt -> get() -> getTransform() -> getTransformation());
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);

                itEnt++;
            }
        }
    }
    utils -> finishRender(3);
}

void EntityMaster::renderEntities(std::vector<PointerEntity> entities, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane, Matrix4f toShadowSpace, GLuint shadowMap){
    if(entities.empty()){
        return;
    }
    shader -> bind();
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    shader -> updateUniform4m("toShadowSpace", toShadowSpace);
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
void EntityMaster::renderEntity(PointerEntity entity, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane){
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