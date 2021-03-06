//
// Created by gabriel on 26.5.2017.
//

#ifndef GAMEENGINE_DEFFEREDRENDERER_H
#define GAMEENGINE_DEFFEREDRENDERER_H

#include <src/deprecated/PostProccessing.h>
#include <src/core/BasicScene.h>
#include <src/components/gui/GuiTexture.h>
#include <src/components/gui/GuiMaster.h>
#include "RenderUtil.h"

class DefferedRenderer : BasicRenderer{
    Fbo multiFbo;
    Fbo fbo, fbo2, fbo3;
    int options = 0;
    PostProccessing pp;
    PointerBasicShader shader;
    std::vector<GuiTexture *> textures;

    inline void setCamera(PointerCamera camera){
        actualCamera = camera;
        updateProjectionMatrix(camera);
    };

    inline void updateProjectionMatrix(PointerCamera camera, PointerBasicShader i_shader = nullptr) {
        if(i_shader){
            i_shader -> bind();
            i_shader -> updateUniform4m(UNIFORM_PROJECTION_MATRIX, camera -> getProjectionMatrix());
        }
        master.updateProjectionMatrix(*camera);
    };
public:
    inline DefferedRenderer(Loader loader, uint width, uint height) :
            multiFbo(Fbo(width, height, FBO_DEPTH_RENDER_BUFFER, 4)),
            fbo(Fbo(width, height, FBO_DEPTH_TEXTURE)),
            fbo2(Fbo(width, height, FBO_DEPTH_TEXTURE)),
            fbo3(Fbo(width, height, FBO_DEPTH_TEXTURE)),
            pp(PostProccessing(loader)),
            shader(PointerBasicShader(new DeferredShader())){

        if(actualCamera && shader -> hasUniform(UNIFORM_PROJECTION_MATRIX)){
            updateProjectionMatrix(actualCamera, shader);
        }
        setCamera(PointerCamera(new Camera()));
        master.init(loader, width, height, *actualCamera, shader);

        textures.push_back(new GuiTexture(fbo.getColourTexture(), Vector2f(0.75f, 0.75f), Vector2f(0.25f, 0.25f)));
        textures.push_back(new GuiTexture(fbo2.getColourTexture(), Vector2f(0.25f, 0.75f), Vector2f(0.25f, 0.25f)));
        textures.push_back(new GuiTexture(fbo3.getColourTexture(), Vector2f(-0.75f, 0.75f), Vector2f(0.25f, 0.25f)));
    }

    inline void cleanUp(void){
        fbo.cleanUp();
        fbo2.cleanUp();
        fbo3.cleanUp();
        pp.cleanUp();
        multiFbo.cleanUp();
    }

    inline void renderScene(BasicScene * scene) override {
        master.getSkyBox() -> renderSky(*scene -> getSky(), *actualCamera);

        renderSceneDeferred(scene, shader, actualCamera, options);
        master.getGui() -> renderGui(getTextures());
    };

    inline void renderSceneDeferred(BasicScene * scene,
                                    PointerBasicShader shader,
                                    PointerCamera actualCamera,
                                    int options) const {
        multiFbo.bindFrameBuffer();

        shader -> bind();

        shader -> updateUniform4m(UNIFORM_VIEW_MATRIX, actualCamera -> getViewMatrix());
        shader -> updateUniform3f(UNIFORM_CAMERA_POSITION, actualCamera -> getPosition());
        glEnable(GL_TEXTURE);
        EntitiesList entities = scene -> getEntities();

        ITERATE_MAP_AUTO(entities, it){ //pre všetky materialy
            if(it -> second.size()){

                RawModel model = it->first->getModel();
                RenderUtil::prepareModel(model, 3);
                RenderUtil::prepareMaterial(*it->first->getMaterial(), *shader, options);

                ITERATE_VECTOR(it->second, i){
                    shader -> updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX,
                                              it -> second[i] -> getTransform() -> getTransformation());
                    glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
                }
            }
        }
        RenderUtil::finishRender(3);

        multiFbo.unbindFrameBuffer();
//    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT1, fbo);
//    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT2, fbo2);
//    multiFbo.resolveToFbo(GL_COLOR_ATTACHMENT3, fbo3);
        multiFbo.resolveToScreen();
//        pp.doPostProcessing(fbo.getColourTexture());


    }

    inline const std::vector<GuiTexture *>& getTextures(void){
        return textures;
    }

};

#endif //GAMEENGINE_DEFFEREDRENDERER_H
