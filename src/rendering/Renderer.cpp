//
// Created by gabriel on 23.9.2016.
//

#include "Renderer.h"
/****************************
 * RENDERERS
 ****************************/


void Renderer::renderScene(BasicScene * scene){
//    if(master.usePostFx()){
//        multiFbo.bindFrameBuffer();
//    }
    if(master.getPostFx()->getUsingPostFx()) {
        master.getPostFx()->startRender();
    }

    if(master.useSkybox()){
        master.getSkyBox() -> renderSky(scene -> getSky(), actualCamera);
    }

    if(master.useShadows()){
        master.getShadow() -> renderShadows(scene -> getEntities(), getLight(), actualCamera);
    }

//    master.getEntity() -> renderWireFrame(scene -> getEntities(), actualCamera);
    master.getEntity() -> renderEntities(scene -> getEntities(),
                                         scene -> getLights(),
                                         actualCamera,
                                         options,
                                         Vector4f(0, 1, 0, -master.getWater() -> getWaterHeight()),
                                         master);
    master.getVoxel() -> render(actualCamera, scene -> getLights(), getSun());

    if(master.useWaters()){
        master.getWater() -> starRenderReflection(actualCamera);
        glEnable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE0);
        if(master.useSkybox()){
            master.getSkyBox() -> renderSky(scene -> getSky(), actualCamera);
        }
        glEnable(GL_CLIP_DISTANCE0);
        master.getEntity() -> renderEntities(scene -> getEntities(),
                                             scene -> getLights(),
                                             actualCamera,
                                             options,
                                             Vector4f(0, 1, 0, -master.getWater() -> getWaterHeight()),
                                             master);

        master.getWater() -> starRenderRefraction(actualCamera);

        master.getEntity() -> renderEntities(scene -> getEntities(),
                                             scene -> getLights(),
                                             actualCamera,
                                             options,
                                             Vector4f(0, -1, 0, master.getWater() -> getWaterHeight() + 1.0f),
                                             master);
        master.getWater() -> finishRender();
        glDisable(GL_CLIP_DISTANCE0);

        master.getWater() -> render(actualCamera, scene -> getLights());
    }
    master.getParticle() -> renderParticles(scene -> getParticles(), actualCamera);

    if(master.getPostFx() -> getUsingPostFx()){
        master.getPostFx() -> stopRender();
        master.getPostFx() -> resolveToFbo(GL_COLOR_ATTACHMENT0, "fbo1");
        master.getPostFx() -> doPostProcessing("fbo1");
    }

//    if(master.usePostFx()){
//        multiFbo.unbindFrameBuffer();
////        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT0, fbo);
////        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT1, fbo);
////        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT2, fbo2);
////        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT3, fbo3);
//        multiFbo.resolveToScreen();
////        pp.doPostProcessing(fbo.getColourTexture());
//    }

    master.getGui() -> renderGui(textures);
}

void Renderer::renderObjects(std::vector<PointerEntity> entities, std::vector<PointerPointLight> lights){
    PointerBasicShader shader = shaders[OBJECT_SHADER];
    GLuint items = 3;
    if(!shader){
        std::cerr << getMessage(CANT_FIND_SHADER) << std::endl;
        return;
    }

    shader -> bind();

    shader -> updateUniformi("options", options);
    shader -> updateUniform4m(UNIFORM_VIEW_MATRIX, actualCamera -> getViewMatrix());

    if(options & FLAG_LIGHT){
        for(unsigned int i=0 ; i<lights.size() ; i++)
            RenderUtil::updateLightUniforms(lights[i], shader, actualCamera, i);
    }

    glEnable(GL_TEXTURE);
    for(unsigned int i=0 ; i< entities.size() ; i++){
        RawModel model = entities[i]->getModel()->getModel();

        shader -> updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, entities[i] -> getTransform() -> getTransformation());
        if(options & FLAG_TEXTURE)
            RenderUtil::prepareMaterial(entities[i]->getModel()->getMaterial(), shader, options);
        RenderUtil::prepareModel(model, items);
        glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
    }
    RenderUtil::finishRender(items);
}

/****************************
 * DEPRECATED
 ***************************/

void Renderer::renderObject(PointerEntity object, std::vector<PointerPointLight> lights){
    PointerBasicShader shader = shaders[OBJECT_SHADER];
    if(!shader)
        return;
    shader -> bind();

    shader -> updateUniform4m(UNIFORM_VIEW_MATRIX, actualCamera -> getViewMatrix());
    //shader -> updateUniform2f("levels", 4);

    for(unsigned int i=0 ; i<lights.size() ; i++)
        RenderUtil::updateLightUniforms(lights[i], shader, actualCamera, i);

    RawModel model = object->getModel()->getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, object->getTransform()->getTransformation());
    RenderUtil::prepareMaterial(object->getModel()->getMaterial(), shader, options);
    RenderUtil::prepareModel(model, 4);
    glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
    RenderUtil::finishRender(4);
}



void Renderer::render(PointerRawModel model){
    RenderUtil::prepareModel(model, 0);
    //glDrawArrays(GL_TRIANGLES, 0, model -> getVertexCount());// - pri použíťí index baferu sa nepoužíva
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    RenderUtil::finishRender(0);
}

void Renderer::render(PointerMaterialedModel materialedModel){
    RawModel model = materialedModel->getModel();
    glEnable(GL_TEXTURE);
    RenderUtil::prepareMaterial(materialedModel->getMaterial(), nullptr, options);
    RenderUtil::prepareModel(model, 1);
    glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
    RenderUtil::finishRender(1);
}