//
// Created by gabriel on 7.1.2017.
//

#include "EntityMaster.h"


void EntityMaster::renderEntities(EntitiesList entities, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane, Master& master){
    if(entities.empty()){
        return;
    }
    shader -> bind();
    shader -> updateUniform4m(VIEW_MATRIX, camera -> getViewMatrix());
    shader -> updateUniform3f("cameraPosition", camera -> getPosition());
    //shader -> updateUniform2f("levels", 4);
    if(master.getShadow() != nullptr){
        shader -> updateUniform4m("toShadowSpace", master.getShadow() -> getToShadowMapSpaceMatrix());
        glBindTexture(GL_TEXTURE_2D, master.getShadow() -> getShadowMap());
    }
        shader -> updateUniform4f("plane", clipPlane);
    glActiveTexture(GL_TEXTURE2);
    for(unsigned int i=0 ; i<lights.size() ; i++){
        RenderUtil::updateLightUniforms(lights[i], shader, camera, i, false);
    }

    glEnable(GL_TEXTURE);
    for (auto it = entities.begin(); it != entities.end(); ++it){ //pre všetky materialy
        if(it -> second.size()){
            auto itEnt = it->second.begin();

            PointerRawModel model = it -> first -> getModel();
            RenderUtil::prepareModel(model, 3);
            RenderUtil::prepareMaterial(it -> first -> getMaterial(), shader, options);

            while(itEnt != it->second.end()){ //prejde všetky entity
                shader -> updateUniform4m(TRANSFORMATION_MATRIX, itEnt -> get() -> getTransform() -> getTransformation());
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);

                itEnt++;
            }
        }
    }
    RenderUtil::finishRender(3);
}

void EntityMaster::renderEntities(std::vector<PointerEntity> entities, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane, Master& master){
    if(entities.empty()){
        return;
    }
    shader -> bind();
    glActiveTexture(GL_TEXTURE3);

    if(master.getShadow() != nullptr) {
        glBindTexture(GL_TEXTURE_2D, master.getShadow() -> getShadowMap());
        shader->updateUniform4m("toShadowSpace", master.getShadow() -> getToShadowMapSpaceMatrix());
    }
    shader -> updateUniform4m(VIEW_MATRIX, camera -> getViewMatrix());
    shader -> updateUniform3f("cameraPosition", camera -> getPosition());
    //shader -> updateUniform2f("levels", 4);
    shader -> updateUniform4f("plane", clipPlane);
    for(unsigned int i=0 ; i<lights.size() ; i++){
        RenderUtil::updateLightUniforms(lights[i], shader, camera, i, false);
    }

    for(PointerEntity entity : entities){
        PointerRawModel model = entity -> getModel() -> getModel();
        glEnable(GL_TEXTURE);

        shader -> updateUniform4m("transformationMatrix", entity -> getTransform() -> getTransformation());

        RenderUtil::prepareMaterial(entity -> getModel() -> getMaterial(), shader, options);
        RenderUtil::prepareModel(model, 3);

        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }
    RenderUtil::finishRender(3);
}
void EntityMaster::renderEntity(PointerEntity entity, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane){
    shader -> bind();

    shader -> updateUniform4m(VIEW_MATRIX, camera -> getViewMatrix());
    shader -> updateUniform3f("cameraPosition", camera -> getPosition());
    //shader -> updateUniform2f("levels", 4);

    for(unsigned int i=0 ; i<lights.size() ; i++){
        RenderUtil::updateLightUniforms(lights[i], shader, camera, i, false);
    }

    PointerRawModel model = entity -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m(TRANSFORMATION_MATRIX, entity -> getTransform() -> getTransformation());

    RenderUtil::prepareMaterial(entity -> getModel() -> getMaterial(), shader, options);
    RenderUtil::prepareModel(model, 3);

    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);

    RenderUtil::finishRender(3);
}

void EntityMaster::renderWireFrame(EntitiesList entities, PointerCamera camera){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    wireFrameShader -> bind();
    wireFrameShader -> updateUniform4m(VIEW_MATRIX, camera -> getViewMatrix());
    wireFrameShader -> updateUniform4m(PROJECTION_MATRIX, camera -> getProjectionMatrix());

    for (auto it = entities.begin(); it != entities.end(); ++it){ //pre všetky materialy
        if(it -> second.size()){
            auto itEnt = it->second.begin();

            PointerRawModel model = it -> first -> getModel();
            RenderUtil::prepareModel(model, 1);

            while(itEnt != it->second.end()){ //prejde všetky entity
                wireFrameShader -> updateUniform4m(TRANSFORMATION_MATRIX, itEnt -> get() -> getTransform() -> getTransformation());
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);

                itEnt++;
            }
        }
    }
    RenderUtil::finishRender(1);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

EntityMaster::EntityMaster(PointerCamera camera){
    RenderUtil::updateProjectionMatrix(shader, camera);
}

void EntityMaster::cleanUp(void){
    shader -> cleanUp();
    delete shader;
}

BasicShader * EntityMaster::getShader(void){
    return shader;
}