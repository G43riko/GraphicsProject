//
// Created by gabriel on 23.9.2016.
//

#include "Renderer.h"


Renderer::Renderer(Loader loader, int width, int height) :
        screen(Screen(width, height, loader)),
        fbo(Fbo(1600, 900, Fbo::DEPTH_RENDER_BUFFER)),
        pp(PostProccessing(loader)),
        wf(WaterFrameBuffer()){
    initShaders();
    setCamera(PointerCamera(new Camera()));
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

}

void Renderer::addShader(std::string key, PointerBasicShader shader){
    shaders[key] = shader;
    if(actualCamera && shader -> hasUniform("projectionMatrix"))
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

/****************************
 * RENDERERS
 ****************************/

void Renderer::renderGui(std::vector<GuiTexture> textures, PointerRawModel model){
    PointerBasicShader shader = shaders["guiShader"];
    if(!shader)
        return;
    shader -> bind();
    prepareModel(model, 0);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for(int i=0 ; i<textures.size() ; i++){
        glBindTexture(GL_TEXTURE_2D, textures[i].getTexture());
        shader -> updateUniform4m("transformationMatrix", Maths::createTransformationMatrix(textures[i].getPosition(), textures[i].getScale()));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    finishRender(0);
}
void Renderer::renderSky(PointerCubeTexture sky, PointerRawModel model){
    PointerBasicShader shader = shaders["skyBoxShader"];
    if(!shader)
        return;

    shader -> updateUniform4m("viewMatrix", actualCamera -> getViewMatrix());
    prepareModel(model, 1);
    sky -> bind();
    GLuint count = model -> getVertexCount();
    glDrawArrays(GL_TRIANGLES, 0, count);
    finishRender(1);



};
void Renderer::renderScene(Scene scene){
    if(usePostFx){
        screen.startRenderToScreen();
    }

    renderObjects(scene.getEntities(), scene.getLights());

    //renderSky(scene.getSky(), scene.getSkyModel());

    if(usePostFx){
        screen.stopRenderToScreen();
        //renderScreen(screen);
        pp.doPostProcessing(screen.getTexture() -> getId());
    }



    renderGui(textures, scene.getGuiModel());
}

void Renderer::renderObjects(std::vector<PointerEntity> entities, std::vector<PointerLight> lights){
    PointerBasicShader shader = shaders["objectShader"];
    if(!shader){
        std::cerr << "Nenašiel sa shader" << std::endl;
        return;
    }

    shader -> bind();

    actualCamera -> input();
    shader -> updateUniform4m("viewMatrix", actualCamera -> getViewMatrix());

    for(int i=0 ; i<lights.size() ; i++)
        updateLightUniforms(lights[i], shader, i);


    glEnable(GL_TEXTURE);
    for(int i=0 ; i< entities.size() ; i++){
        PointerRawModel model = entities[i] -> getModel() -> getModel();

        shader -> updateUniform4m("transformationMatrix", entities[i] -> getTransform() -> getTransformation());
        prepareMaterial(entities[i] -> getModel() -> getMaterial(), shader);
        prepareModel(model, 4);
        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }
    finishRender(4);
}

void Renderer::renderScreen(Screen screen) {
    PointerBasicShader shader = shaders["postFxShader"];
    if(!shader)
        return;
    shader -> bind();

    screen.setUniforms(shader);

    prepareModel(screen.getModel(), 0);
    glDisable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    screen.getTexture() -> bind();

    shader -> updateUniform4m("transformationMatrix", screen.getTransformationMatrix());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, screen.getModel() -> getVertexCount());

    //shader -> unbind();
    glEnable(GL_DEPTH_TEST);
    finishRender(0);
}

void Renderer::prepareRenderer(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1){
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::prepareModel(PointerRawModel model, GLuint numberOfAttributes){
    glBindVertexArray(model -> getVaoID());
    for(GLuint i=0 ; i<=numberOfAttributes ; i++)
        glEnableVertexAttribArray(i);
}

void Renderer::prepareMaterial(PointerMaterial material, PointerBasicShader shader){
    if(shader)
        shader -> connectTextures();

    material -> getDiffuse() -> bind(GL_TEXTURE0);

    PointerTexture2D normal = material -> getNormal();
    if(normal)
        normal -> bind(GL_TEXTURE1);
}

void Renderer::finishRender(GLuint numberOfAttributes){
    for(GLuint i=0 ; i<=numberOfAttributes ; i++)
        glDisableVertexAttribArray(i);

    glBindVertexArray(0);
}

void Renderer::updateLightUniforms(PointerLight light, PointerBasicShader shader, int index){
    shader -> updateUniform3f("lightPositionEyeSpace[" + std::to_string(index) + "]",
                              getEyeSpacePosition(light, actualCamera -> getViewMatrix()));
    shader -> updateUniform3f("lightColor[" + std::to_string(index) + "]",
                              light -> getColor());
    shader -> updateUniform3f("attenuation[" + std::to_string(index) + "]",
                              light -> getAttenuation());
}

Vector3f Renderer::getEyeSpacePosition(PointerLight light, glm::mat4 view){
    Vector3f position = light -> getPosition();

    float x = view[0][0] * position.x + view[1][0] * position.y + view[2][0] * position.z + view[3][0];
    float y = view[0][1] * position.x + view[1][1] * position.y + view[2][1] * position.z + view[3][1];
    float z = view[0][2] * position.x + view[1][2] * position.y + view[2][2] * position.z + view[3][2];
    /*
    float x = view[0][0] * position.x + view[0][1] * position.y + view[0][2] * position.z + view[0][3];
    float y = view[1][0] * position.x + view[1][1] * position.y + view[1][2] * position.z + view[1][3];
    float z = view[2][0] * position.x + view[2][1] * position.y + view[2][2] * position.z + view[2][3];
    */

    return Vector3f(x, y, z);
};

/****************************
 * DEPRECATED
 ***************************/
void Renderer::renderObject(PointerEntity object, std::vector<PointerLight> lights){
    PointerBasicShader shader = shaders["objectShader"];
    if(!shader)
        return;
    shader -> bind();

    actualCamera -> input();
    shader -> updateUniform4m("viewMatrix", actualCamera -> getViewMatrix());
    //shader -> updateUniform2f("levels", 4);

    for(unsigned int i=0 ; i<lights.size() ; i++)
        updateLightUniforms(lights[i], shader, i);

    PointerRawModel model = object -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m("transformationMatrix", object->getTransform()->getTransformation());
    prepareMaterial(object -> getModel() -> getMaterial(), shader);
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
    //shader -> updateUniform2f("levels", 4);

    shader -> updateUniform3f("lightPosition", light -> getPosition());
    shader -> updateUniform3f("lightColor", light -> getColor());

    PointerRawModel model = entity -> getModel() -> getModel();
    glEnable(GL_TEXTURE);

    shader -> updateUniform4m("transformationMatrix", entity->getTransform()->getTransformation());

    prepareMaterial(entity -> getModel() -> getMaterial(), shader);
    prepareModel(model, 3);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    finishRender(3);
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
    prepareMaterial(materialedModel -> getMaterial(), nullptr);
    prepareModel(model, 1);
    glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    finishRender(1);
}
