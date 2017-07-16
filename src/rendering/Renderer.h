//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RENDERER_H
#define GRAPHICSPROJECT_RENDERER_H


#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtx/string_cast.hpp>
#include <src/core/BasicRenderer.h>
#include "src/rendering/shader/DeferredShader.h"
#include "src/rendering/shader/ShadowShader.h"
#include <src/Messages.h>
#include "DefferedRenderer.h"

class Renderer : public BasicRenderer{
//    DefferedRenderer defferedRenderer;

    inline void setCamera(PointerCamera camera){
        actualCamera = camera;
        updateProjectionMatrix(*camera);
    };
    int options = Flag::TEXTURE | Flag::NORMAL_MAP | Flag::LIGHT | Flag::SPECULAR | Flag::FOG;

    std::map<std::string, PointerBasicShader> shaders;
public:
    struct Flag{
        constexpr static u_char TEXTURE         = 0x01; // hex for 0000 0001
        constexpr static u_char NORMAL_MAP      = 0x02; // hex for 0000 0010
        constexpr static u_char LIGHT           = 0x04; // hex for 0000 0100
        constexpr static u_char SPECULAR        = 0x08; // hex for 0000 1000
        constexpr static u_char FOG             = 0x10; // hex for 0001 0000
        constexpr static u_char ENVIRONMENTAL   = 0x20; // hex for 0010 0000
        constexpr static u_char WATER           = 0x40; // hex for 0100 0000
        constexpr static u_char SHADOW          = 0x80; // hex for 1000 0000
    };
//    const static u_char FLAG_TEXTURE         = 0x01; // hex for 0000 0001
//    const static u_char FLAG_NORMAL_MAP      = 0x02; // hex for 0000 0010
//    const static u_char FLAG_LIGHT           = 0x04; // hex for 0000 0100
//    const static u_char FLAG_SPECULAR        = 0x08; // hex for 0000 1000
//    const static u_char FLAG_FOG             = 0x10; // hex for 0001 0000
//    const static u_char FLAG_ENVIRONMENTAL   = 0x20; // hex for 0010 0000
//    const static u_char FLAG_WATER           = 0x40; // hex for 0100 0000
//    const static u_char FLAG_SHADOW          = 0x80; // hex for 1000 0000

    inline Renderer(Loader& loader, uint width, uint height){
        initShaders();
        setCamera(PointerCamera(new Camera()));
        master.init(loader, width, height, *actualCamera, shaders[SHADOW_SHADER]);
//    textures.push_back(GuiTexture(shadowMaster->getShadowMap(), Vector2f(-1, 1), Vector2f(1)));
    }

    void renderObjects(std::vector<PointerEntity>, std::vector<PointerPointLight>);
    void renderScene(BasicScene * scene) override;

    inline void update(const float delta) override{
        master.update(delta);
    };

    inline void input(void) override {
        if(Input::getKeyUp(GLFW_KEY_1)){
            toggleOption(Flag::LIGHT);
        }
        if(Input::getKeyUp(GLFW_KEY_2)){
            toggleOption(Flag::SPECULAR);
        }
        if(Input::getKeyUp(GLFW_KEY_3)){
            toggleOption(Flag::NORMAL_MAP);
        }
        if(Input::getKeyUp(GLFW_KEY_4)){
            toggleOption(Flag::TEXTURE);
        }
        if(Input::getKeyUp(GLFW_KEY_5)){
            toggleOption(Flag::FOG);
        }
    };



//    inline void updateProjectionMatrix(PointerCamera camera, PointerBasicShader shader = nullptr) {
//        if(shader){
//            shader -> bind();
//            shader -> updateUniform4m(UNIFORM_PROJECTION_MATRIX, camera -> getProjectionMatrix());
//        }
//        else {
//            ITERATE_MAP_AUTO(shaders, it){
//                if (it -> second -> hasUniform(UNIFORM_PROJECTION_MATRIX)) {
//                    it -> second -> bind();
//                    it -> second -> updateUniform4m(UNIFORM_PROJECTION_MATRIX, camera->getProjectionMatrix());
//                }
//            }
//        }
//        master.updateProjectionMatrix(*camera);
//    };
    inline void updateProjectionMatrix(const BasicCamera& camera, PointerBasicShader shader = nullptr) {
        if(shader){
            shader -> bind();
            shader -> updateUniform4m(UNIFORM_PROJECTION_MATRIX, camera.getProjectionMatrix());
        }
        else {
            ITERATE_MAP_AUTO(shaders, it){
                if (it -> second -> hasUniform(UNIFORM_PROJECTION_MATRIX)) {
                    it -> second -> bind();
                    it -> second -> updateUniform4m(UNIFORM_PROJECTION_MATRIX, camera.getProjectionMatrix());
                }
            }
        }
        master.updateProjectionMatrix(camera);
    };


    inline void init3D(void) override {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    };

    inline void addShader(std::string key, PointerBasicShader shader){
        shaders[key] = shader;
        if(actualCamera && shader -> hasUniform(UNIFORM_PROJECTION_MATRIX)){
            updateProjectionMatrix(*actualCamera, shader);
        }
    };

    inline void cleanUp(void) override{
//        defferedRenderer.cleanUp();

        ITERATE_MAP_AUTO(shaders, it){
            it -> second -> cleanUp();
        }
        shaders.clear();
        master.cleanUp();
    };

    inline void prepareRenderer(const float red  = 0,
                                const float green  = 0,
                                const float blue  = 0,
                                const float alpha = 1) override{
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };

    inline void initShaders(void){
        if(master.useShadows()){
            addShader(SHADOW_SHADER, PointerBasicShader(new ShadowShader()));
        };
        addShader(DEFERRED_SHADER, PointerBasicShader(new DeferredShader()));
    };

    inline void turnOnOption(u_char val){ options |= val; }
    inline void turnOffOption(u_char val){ options &= ~val; }
    inline void toggleOption(u_char val){ options ^= val; }


    //DEPRECATED

//    void render(const RawModel& model);
//    void render(const MaterialedModel& model);
//    void renderObject(Entity& entity, std::vector<PointerPointLight> lights);
};


#endif //GRAPHICSPROJECT_RENDERER_H
