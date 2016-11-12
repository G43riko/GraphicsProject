//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RENDERER_H
#define GRAPHICSPROJECT_RENDERER_H


#include "model/RawModel.h"
#include "model/MaterialedModel.h"
#include "model/Entity.h"
#include "../entities/Light.h"
#include "../entities/Scene.h"
#include <iostream>
#include "Camera.h"
#include <glm/mat4x4.hpp>
#include "../utils/Maths.h"
#include "../postProccessing/Screen.h"
#include "GuiTexture.h"
#include <glm/gtx/string_cast.hpp>

#include "shader/EntityShader.cpp"
#include "shader/PostFxShader.cpp"
#include "shader/ObjectShader.cpp"
#include "shader/GuiShader.cpp"
#include "shader/SkyBoxShader.cpp"
#include "shader/ColorShader.cpp"
#include "../postProccessing/PostProccessing.h"
#include "../water/WaterFrameBuffer.h"

class Screen;
class Scene;

class Renderer {
    public:
        Renderer(Loader, int, int );
        void renderGui(std::vector<GuiTexture>, PointerRawModel);
        void renderScene(Scene);
        void renderSky(CubeTexture, PointerRawModel);
        void renderObjects(std::vector<PointerEntity>, std::vector<PointerLight>);
        void renderScreen(Screen);
        void setCamera(PointerCamera);
        void updateProjectionMatrix(PointerCamera, PointerBasicShader = nullptr);
        void prepareRenderer(GLfloat, GLfloat, GLfloat, GLfloat);
        void init3D(void);
        void addShader(std::string, PointerBasicShader);
        void cleanUp(void);
        void initShaders(void);
        void addTexture(GuiTexture texture){
            textures.push_back(texture);
        }
        void setPostFx(bool val){
            usePostFx = val;
        }
        //DEPRECATED
        void render(PointerRawModel);
        void render(PointerMaterialedModel);
        void renderEntity(PointerEntity);
        void renderObject(PointerEntity, std::vector<PointerLight>);
    private:
        WaterFrameBuffer wf;
        Fbo fbo;
        PostProccessing pp;
        std::map<std::string, PointerBasicShader> shaders;
        Light * light = new Light(Vector3f(0, 0, 0), Vector3f(1, 1, 1));
        PointerCamera actualCamera = nullptr;
        Screen screen;
        bool usePostFx = false;
        std::vector<GuiTexture> textures;
        //PRIVATE METHODS
        void updateLightUniforms(PointerLight, PointerBasicShader, int);
        Vector3f getEyeSpacePosition(PointerLight, glm::mat4);
        void prepareModel(PointerRawModel, GLuint);
        void prepareMaterial(PointerMaterial, PointerBasicShader);
        void finishRender(GLuint);


};


#endif //GRAPHICSPROJECT_RENDERER_H
