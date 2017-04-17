//
// Created by gabriel on 23.9.2016.
//

#include "Renderer.h"
#include "../components/postProccessing/PostFxMaster.h"


#define SHADOW_SHADER "shadowShader"
#define OBJECT_SHADER "objectShader"
#define POSTFX_SHADER "postFxShader"
#define PARTICLE_SHADER "particleShader"
#define DEFERRED_SHADER "deferredShader"

Renderer::Renderer(Loader loader, int width, int height) :
//        screen(Screen(width, height, loader)),
        multiFbo(Fbo(width, height, Fbo::DEPTH_RENDER_BUFFER,4)),
        fbo(Fbo(width, height, Fbo::DEPTH_TEXTURE)),
        fbo2(Fbo(width, height, Fbo::DEPTH_TEXTURE)),
        fbo3(Fbo(width, height, Fbo::DEPTH_TEXTURE)),
        pp(PostProccessing(loader)),
        wf(WaterFrameBuffer()){
    DEBUG("------------------------------------------");
    DEBUG("Renderer::Renderer - start: " << glfwGetTime());
    initShaders();
    DEBUG("Renderer::Renderer - after initShaders: " << glfwGetTime());

//    textures.push_back(GuiTexture(wf.getRefractionDepthTexture(), Vector2f(0.75f, 0.75f), Vector2f(0.25f, 0.25f)));
//    textures.push_back(GuiTexture(wf.getRefractionTexture(), Vector2f(-0.75f, 0.75f), Vector2f(0.25f, 0.25f)));

//    textures.push_back(GuiTexture(fbo.getColourTexture(), Vector2f(0.75f, 0.75f), Vector2f(0.25f, 0.25f)));
//    textures.push_back(GuiTexture(fbo2.getColourTexture(), Vector2f(0.25f, 0.75f), Vector2f(0.25f, 0.25f)));
//    textures.push_back(GuiTexture(fbo3.getColourTexture(), Vector2f(-0.75f, 0.75f), Vector2f(0.25f, 0.25f)));

    DEBUG("Renderer::Renderer - create gui textures: " << glfwGetTime());
    setCamera(PointerCamera(new Camera()));
    DEBUG("Renderer::Renderer - setCamera: " << glfwGetTime());

    master.init(loader, width, height, actualCamera, shaders[SHADOW_SHADER], shaders[PARTICLE_SHADER]);

    DEBUG("Renderer::Renderer - initShaders: " << glfwGetTime());


//    textures.push_back(GuiTexture(shadowMaster->getShadowMap(), Vector2f(-1, 1), Vector2f(1)));
    DEBUG("------------------------------------------");
}
void Renderer::prepareRenderer(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setCamera(PointerCamera camera){
    actualCamera = camera;
    updateProjectionMatrix(camera);
}

void Renderer::updateProjectionMatrix(PointerCamera camera, PointerBasicShader shader){
    if(shader){
        shader -> bind();
        shader -> updateUniform4m(PROJECTION_MATRIX, camera -> getProjectionMatrix());
    }
    else {
        for (auto it = shaders.begin(); it != shaders.end(); ++it){
            if (it->second->hasUniform(PROJECTION_MATRIX)) {
                it->second->bind();
                it->second->updateUniform4m(PROJECTION_MATRIX, camera->getProjectionMatrix());
            }
        }
    }
    master.updateProjectionMatrix(camera);
}

void Renderer::cleanUp(void){
    fbo.cleanUp();
    fbo2.cleanUp();
    fbo3.cleanUp();
    pp.cleanUp();
    wf.cleanUp();
    multiFbo.cleanUp();

//    screen.cleanUp();

    for (auto it = shaders.begin(); it != shaders.end(); ++it){
        it -> second -> cleanUp();
    }
    shaders.clear();

    delete light;
    master.cleanUp();

}

void Renderer::initShaders(void){
    if(master.useParticles()){
        addShader(PARTICLE_SHADER, PointerBasicShader(new ParticleShader()));
    };
    if(master.useShadows()){
        addShader(SHADOW_SHADER, PointerBasicShader(new ShadowShader()));
    };
    addShader(DEFERRED_SHADER, PointerBasicShader(new DeferredShader()));

}

void Renderer::addShader(std::string key, PointerBasicShader shader){
    shaders[key] = shader;
    if(actualCamera && shader -> hasUniform(PROJECTION_MATRIX))
        updateProjectionMatrix(actualCamera, shader);
}

void Renderer::init3D(){
//    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

/****************************
 * RENDERERS
 ****************************/

void Renderer::renderSceneDeferred(BasicScene * scene){
    multiFbo.bindFrameBuffer();
    master.getSkyBox() -> renderSky(scene -> getSky(), actualCamera);

    PointerBasicShader shader = shaders[DEFERRED_SHADER];

    shader -> bind();

    shader -> updateUniform4m(VIEW_MATRIX, actualCamera -> getViewMatrix());
    shader -> updateUniform3f("cameraPosition", actualCamera -> position);
    glEnable(GL_TEXTURE);
    EntitiesList entities = scene -> getEntities();

    for (auto it = entities.begin(); it != entities.end(); ++it){ //pre všetky materialy
        if(it -> second.size()){
            auto itEnt = it->second.begin();

            PointerRawModel model = it->first -> getModel();
            RenderUtil::prepareModel(model, 3);
            RenderUtil::prepareMaterial(it->first-> getMaterial(), shader, options);

            while(itEnt != it->second.end()){ //prejde všetky entity
                shader -> updateUniform4m(TRANSFORMATION_MATRIX, itEnt -> get() -> getTransform() -> getTransformation());
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);

                itEnt++;
            }
        }
    }
    RenderUtil::finishRender(3);

    multiFbo.unbindFrameBuffer();
    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT1, fbo);
    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT2, fbo2);
    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT3, fbo3);
    multiFbo.resolveToScreen();
//        pp.doPostProcessing(fbo.getColourTexture());


    master.getGui() -> renderGui(textures);
}

void Renderer::renderScene(BasicScene * scene){
    if(master.usePostFx()){
        multiFbo.bindFrameBuffer();
    }
    master.getPostFx() -> startRender();

    if(master.useSkybox()){
        master.getSkyBox() -> renderSky(scene -> getSky(), actualCamera);
    }

    if(master.useShadows()){
        master.getShadow() -> renderShadows(scene -> getEntities(), sun, actualCamera);
    }

    //entityMaster -> renderWireFrame(scene.getEntities(), actualCamera);
    master.getEntity() -> renderEntities(scene -> getEntities(), scene -> getLights(), actualCamera, options, Vector4f(0, 1, 0, -master.getWater() -> getWaterHeight()), master);
    master.getVoxel() -> render(actualCamera);

    if(master.useWaters()){
        master.getWater() -> starRenderReflection(actualCamera);
        glEnable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE0);
        if(master.useSkybox()){
            master.getSkyBox() -> renderSky(scene -> getSky(), actualCamera);
        }
        glEnable(GL_CLIP_DISTANCE0);
        master.getEntity() -> renderEntities(scene -> getEntities(), scene -> getLights(), actualCamera, options, Vector4f(0, 1, 0, -master.getWater() -> getWaterHeight()), master);

        master.getWater() -> starRenderRefraction(actualCamera);

        master.getEntity() -> renderEntities(scene -> getEntities(), scene -> getLights(), actualCamera, options, Vector4f(0, -1, 0, master.getWater() -> getWaterHeight() + 1.0f), master);
        master.getWater() -> finishRender();
        glDisable(GL_CLIP_DISTANCE0);

        master.getWater() -> render(actualCamera, scene -> getLights());
    }
    master.getParticle() -> renderParticles(scene -> getParticles(), actualCamera);

    if(master.getPostFx()->getUsingPostFx()){
        master.getPostFx()->stopRender();
        master.getPostFx()->resolveToFbo(GL_COLOR_ATTACHMENT0, "fbo1");
        master.getPostFx()->doPostProcessing("fbo1");
    }

    if(master.usePostFx()){
        multiFbo.unbindFrameBuffer();
//        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT0, fbo);
//        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT1, fbo);
//        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT2, fbo2);
//        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT3, fbo3);
        multiFbo.resolveToScreen();
//        pp.doPostProcessing(fbo.getColourTexture());
    }

    master.getGui() -> renderGui(textures);
}

void Renderer::renderObjects(std::vector<PointerEntity> entities, std::vector<PointerPointLight> lights){
    PointerBasicShader shader = shaders[OBJECT_SHADER];
    GLuint items = 3;
    if(!shader){
        std::cerr << "Nenašiel sa shader" << std::endl;
        return;
    }

    shader -> bind();

    shader -> updateUniformi("options", options);
    shader -> updateUniform4m(VIEW_MATRIX, actualCamera -> getViewMatrix());

    if(options & FLAG_LIGHT){
        for(unsigned int i=0 ; i<lights.size() ; i++)
            RenderUtil::updateLightUniforms(lights[i], shader, actualCamera, i);
    }

    glEnable(GL_TEXTURE);
    for(unsigned int i=0 ; i< entities.size() ; i++){
        PointerRawModel model = entities[i] -> getModel() -> getModel();

        shader -> updateUniform4m(TRANSFORMATION_MATRIX, entities[i] -> getTransform() -> getTransformation());
        if(options & FLAG_TEXTURE)
            RenderUtil::prepareMaterial(entities[i] -> getModel() -> getMaterial(), shader, options);
        RenderUtil::prepareModel(model, items);
        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }
    RenderUtil::finishRender(items);
}

/****************************
 * DEPRECATED
 ***************************/

void Renderer::renderScreen(Screen screen) {
    PointerBasicShader shader = shaders[POSTFX_SHADER];
    if(!shader)
        return;
    shader -> bind();

    screen.setUniforms(shader);

    RenderUtil::prepareModel(screen.getModel(), 0);
    glDisable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    screen.getTexture() -> bind();

    shader -> updateUniform4m(TRANSFORMATION_MATRIX, screen.getTransformationMatrix());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, screen.getModel() -> getVertexCount());

    //shader -> unbind();
    glEnable(GL_DEPTH_TEST);
    RenderUtil::finishRender(0);
}

void Renderer::renderObject(PointerEntity object, std::vector<PointerPointLight> lights){
    PointerBasicShader shader = shaders[OBJECT_SHADER];
    if(!shader)
        return;
    shader -> bind();

    shader -> updateUniform4m(VIEW_MATRIX, actualCamera -> getViewMatrix());
    //shader -> updateUniform2f("levels", 4);

    for(unsigned int i=0 ; i<lights.size() ; i++)
        RenderUtil::updateLightUniforms(lights[i], shader, actualCamera, i);

    PointerRawModel model = object -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m(TRANSFORMATION_MATRIX, object->getTransform()->getTransformation());
    RenderUtil::prepareMaterial(object -> getModel() -> getMaterial(), shader, options);
    RenderUtil::prepareModel(model, 4);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    RenderUtil::finishRender(4);
}



void Renderer::render(PointerRawModel model){
    RenderUtil::prepareModel(model, 0);
    //glDrawArrays(GL_TRIANGLES, 0, model -> getVertexCount());// - pri použíťí index baferu sa nepoužíva
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    RenderUtil::finishRender(0);
}

void Renderer::render(PointerMaterialedModel materialedModel){
    PointerRawModel model = materialedModel -> getModel();
    glEnable(GL_TEXTURE);
    RenderUtil::prepareMaterial(materialedModel -> getMaterial(), nullptr, options);
    RenderUtil::prepareModel(model, 1);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    RenderUtil::finishRender(1);
}
void Renderer::update(float delta) {
    master.update(delta);
}

void Renderer::input(void) {
    //actualCamera -> input();

    if(Input::getKeyUp(GLFW_KEY_1))
        toggleOption(FLAG_LIGHT);
    if(Input::getKeyUp(GLFW_KEY_2))
        toggleOption(FLAG_SPECULAR);
    if(Input::getKeyUp(GLFW_KEY_3))
        toggleOption(FLAG_NORMAL_MAP);
    if(Input::getKeyUp(GLFW_KEY_4))
        toggleOption(FLAG_TEXTURE);
    if(Input::getKeyUp(GLFW_KEY_5))
        toggleOption(FLAG_FOG);
}
