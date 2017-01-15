//
// Created by gabriel on 23.9.2016.
//

#include "Renderer.h"


Renderer::Renderer(Loader loader, int width, int height) :
        screen(Screen(width, height, loader)),
        multiFbo(Fbo(width, height, Fbo::DEPTH_RENDER_BUFFER,4)),
        fbo(Fbo(width, height, Fbo::DEPTH_TEXTURE)),
        fbo2(Fbo(width, height, Fbo::DEPTH_TEXTURE)),
        fbo3(Fbo(width, height, Fbo::DEPTH_TEXTURE)),
        pp(PostProccessing(loader)),
        wf(WaterFrameBuffer()){
    initShaders();

//    textures.push_back(GuiTexture(wf.getRefractionDepthTexture(), Vector2f(0.75f, 0.75f), Vector2f(0.25f, 0.25f)));
//    textures.push_back(GuiTexture(wf.getRefractionTexture(), Vector2f(-0.75f, 0.75f), Vector2f(0.25f, 0.25f)));

    textures.push_back(GuiTexture(fbo.getColourTexture(), Vector2f(0.75f, 0.75f), Vector2f(0.25f, 0.25f)));
    textures.push_back(GuiTexture(fbo2.getColourTexture(), Vector2f(0.25f, 0.75f), Vector2f(0.25f, 0.25f)));
    textures.push_back(GuiTexture(fbo3.getColourTexture(), Vector2f(-0.75f, 0.75f), Vector2f(0.25f, 0.25f)));
    setCamera(PointerCamera(new Camera()));

    shadowMaster    = new ShadowMaster(&utils, shaders["shadowShader"], getActualCamera());
    guiMaster       = new GuiMaster(&utils, shaders["guiShader"], loader);
    skyBoxMaster    = new SkyBoxMaster(&utils, shaders["skyBoxShader"], loader);
    particleMaster  = new ParticleMaster(&utils, shaders["particleShader"], loader);
    entityMaster    = new EntityMaster(&utils, shaders["entityShader"]);
    waterMaster     = new WaterMaster(&utils, shaders["waterShader"], loader);

//    textures.push_back(GuiTexture(shadowMaster->getShadowMap(), Vector2f(-1, 1), Vector2f(1)));
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

void Renderer::cleanUp(void){
    fbo.cleanUp();
    fbo2.cleanUp();
    multiFbo.cleanUp();
    screen.cleanUp();

    for (auto it = shaders.begin(); it != shaders.end(); ++it)
        it -> second -> cleanUp();
    delete light;
}

void Renderer::initShaders(void){
    addShader("guiShader", PointerBasicShader(new GuiShader()));
    addShader("entityShader", PointerBasicShader(new EntityShader()));
    addShader("postFxShader", PointerBasicShader(new PostFxShader()));
    addShader("objectShader", PointerBasicShader(new ObjectShader()));
    addShader("colorShader", PointerBasicShader(new ColorShader()));
    addShader("skyBoxShader", PointerBasicShader(new SkyBoxShader()));
    addShader("particleShader", PointerBasicShader(new ParticleShader()));
    addShader("shadowShader", PointerBasicShader(new ShadowShader()));
    addShader("waterShader", PointerBasicShader(new WaterShader()));
    addShader("deferredShader", PointerBasicShader(new DeferredShader()));

}

void Renderer::addShader(std::string key, PointerBasicShader shader){
    shaders[key] = shader;
    if(actualCamera && shader -> hasUniform("projectionMatrix"))
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

void Renderer::renderSceneDeferred(Scene scene){
    multiFbo.bindFrameBuffer();
    skyBoxMaster -> renderSky(scene.getSky(), actualCamera);

    PointerBasicShader shader = shaders["deferredShader"];

    shader -> bind();
    shader -> updateUniform4m("viewMatrix", actualCamera -> getViewMatrix());
    shader -> updateUniform3f("cameraPosition", actualCamera -> position);
    glEnable(GL_TEXTURE);
    EntitiesList entities = scene.getEntities();

    for (auto it = entities.begin(); it != entities.end(); ++it){ //pre všetky materialy
        if(it -> second.size()){
            auto itEnt = it->second.begin();

            PointerRawModel model = it->first -> getModel();
            utils.prepareModel(model, 3);
            utils.prepareMaterial(it->first-> getMaterial(), shader, options);

            while(itEnt != it->second.end()){ //prejde všetky entity
                shader -> updateUniform4m("transformationMatrix", itEnt -> get() -> getTransform() -> getTransformation());
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);

                itEnt++;
            }
        }
    }
    utils.finishRender(3);

    multiFbo.unbindFrameBuffer();
    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT1, fbo);
    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT2, fbo2);
    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT3, fbo3);
    multiFbo.resolveToScreen();
//        pp.doPostProcessing(fbo.getColourTexture());

    guiMaster -> renderGui(textures);
}

void Renderer::renderScene(Scene scene){
    if(usePostFx){
        multiFbo.bindFrameBuffer();
    }

    //renderObjects(scene.getEntities(), scene.getLights());
    skyBoxMaster -> renderSky(scene.getSky(), actualCamera);

    if(useShadows){
        shadowMaster -> renderShadows(scene.getEntities(), sun, actualCamera);
    }

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    entityMaster -> renderEntities(scene.getEntities(), scene.getLights(), actualCamera, options, Vector4f(0, 1, 0, -waterMaster -> getWaterHeight()), shadowMaster->getToShadowMapSpaceMatrix(), shadowMaster->getShadowMap());
    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    if(useWaters){
        waterMaster -> starRenderReflection(actualCamera);
        glEnable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE0);
        skyBoxMaster -> renderSky(scene.getSky(), actualCamera);
        glEnable(GL_CLIP_DISTANCE0);
        entityMaster -> renderEntities(scene.getEntities(), scene.getLights(), actualCamera, options, Vector4f(0, 1, 0, -waterMaster -> getWaterHeight()), shadowMaster->getToShadowMapSpaceMatrix(), shadowMaster->getShadowMap());

        waterMaster -> starRenderRefraction(actualCamera);

        entityMaster -> renderEntities(scene.getEntities(), scene.getLights(), actualCamera, options, Vector4f(0, -1, 0, waterMaster -> getWaterHeight() + 1.0f), shadowMaster->getToShadowMapSpaceMatrix(), shadowMaster->getShadowMap());
        waterMaster -> finishRender();
        glDisable(GL_CLIP_DISTANCE0);
    }

    waterMaster -> render(actualCamera, scene.getLights());

    particleMaster -> renderParticles(scene.getParticles(), actualCamera);
    if(usePostFx){
        multiFbo.unbindFrameBuffer();
        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT1, fbo);
        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT2, fbo2);
        multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT3, fbo3);
        multiFbo.resolveToScreen();
//        pp.doPostProcessing(fbo.getColourTexture());
    }

    guiMaster -> renderGui(textures);
}

void Renderer::renderObjects(std::vector<PointerEntity> entities, std::vector<PointerPointLight> lights){
    PointerBasicShader shader = shaders["objectShader"];
    GLuint items = 3;
    if(!shader){
        std::cerr << "Nenašiel sa shader" << std::endl;
        return;
    }

    shader -> bind();

    shader -> updateUniformi("options", options);
    shader -> updateUniform4m("viewMatrix", actualCamera -> getViewMatrix());

    if(options & FLAG_LIGHT){
        for(unsigned int i=0 ; i<lights.size() ; i++)
            utils.updateLightUniforms(lights[i], shader, actualCamera, i);
    }

    glEnable(GL_TEXTURE);
    for(unsigned int i=0 ; i< entities.size() ; i++){
        PointerRawModel model = entities[i] -> getModel() -> getModel();

        shader -> updateUniform4m("transformationMatrix", entities[i] -> getTransform() -> getTransformation());
        if(options & FLAG_TEXTURE)
            utils.prepareMaterial(entities[i] -> getModel() -> getMaterial(), shader, options);
        utils.prepareModel(model, items);
        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }
    utils.finishRender(items);
}

void Renderer::renderScreen(Screen screen) {
    PointerBasicShader shader = shaders["postFxShader"];
    if(!shader)
        return;
    shader -> bind();

    screen.setUniforms(shader);

    utils.prepareModel(screen.getModel(), 0);
    glDisable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    screen.getTexture() -> bind();

    shader -> updateUniform4m("transformationMatrix", screen.getTransformationMatrix());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, screen.getModel() -> getVertexCount());

    //shader -> unbind();
    glEnable(GL_DEPTH_TEST);
    utils.finishRender(0);
}


/****************************
 * DEPRECATED
 ***************************/
void Renderer::renderObject(PointerEntity object, std::vector<PointerPointLight> lights){
    PointerBasicShader shader = shaders["objectShader"];
    if(!shader)
        return;
    shader -> bind();

    shader -> updateUniform4m("viewMatrix", actualCamera -> getViewMatrix());
    //shader -> updateUniform2f("levels", 4);

    for(unsigned int i=0 ; i<lights.size() ; i++)
        utils.updateLightUniforms(lights[i], shader, actualCamera, i);

    PointerRawModel model = object -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m("transformationMatrix", object->getTransform()->getTransformation());
    utils.prepareMaterial(object -> getModel() -> getMaterial(), shader, options);
    utils.prepareModel(model, 4);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    utils.finishRender(4);
}



void Renderer::render(PointerRawModel model){
    utils.prepareModel(model, 0);
    //glDrawArrays(GL_TRIANGLES, 0, model -> getVertexCount());// - pri použíťí index baferu sa nepoužíva
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    utils.finishRender(0);
}

void Renderer::render(PointerMaterialedModel materialedModel){
    PointerRawModel model = materialedModel -> getModel();
    glEnable(GL_TEXTURE);
    utils.prepareMaterial(materialedModel -> getMaterial(), nullptr, options);
    utils.prepareModel(model, 1);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    utils.finishRender(1);
}
void Renderer::update(float delta) {
    if(waterMaster){
        waterMaster -> update(delta);
    }
}

void Renderer::input(void) {
    //actualCamera -> input();

    if(Input::getKeyUp(GLFW_KEY_1))
        toggleOption(Renderer::FLAG_LIGHT);
    if(Input::getKeyUp(GLFW_KEY_2))
        toggleOption(Renderer::FLAG_SPECULAR);
    if(Input::getKeyUp(GLFW_KEY_3))
        toggleOption(Renderer::FLAG_NORMAL_MAP);
    if(Input::getKeyUp(GLFW_KEY_4))
        toggleOption(Renderer::FLAG_TEXTURE);
    if(Input::getKeyUp(GLFW_KEY_5))
        toggleOption(Renderer::FLAG_FOG);
}
