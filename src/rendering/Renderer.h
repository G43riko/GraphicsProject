//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RENDERER_H
#define GRAPHICSPROJECT_RENDERER_H


#include "../game/Scene.h"
#include <iostream>
#include "Camera.h"
#include <glm/mat4x4.hpp>
#include <glm/gtx/string_cast.hpp>
#include <src/game/Scene.h>
#include <src/core/BasicRenderer.h>
#include "src/rendering/shader/ParticleShader.h"
#include "src/rendering/shader/DeferredShader.h"
#include "src/rendering/shader/ShadowShader.h"
#include "RenderUtil.h"
#include <src/Messages.h>
#include "../components/postProccessing/Screen.h"


class Screen;
class Scene;

class Renderer : public BasicRenderer{
    public:
        Renderer(Loader, int, int );
        void renderSceneDeferred(BasicScene * scene) override;
        void renderScene(BasicScene * scene) override;
        void renderObjects(std::vector<PointerEntity>, std::vector<PointerPointLight>);
        void renderScreen(Screen screen);
        void updateProjectionMatrix(PointerCamera, PointerBasicShader = nullptr);
        void init3D(void) override;
        void update(float delta) override;
        void input(void) override;
        void addShader(std::string key, PointerBasicShader shader);
        void cleanUp(void) override;
        void initShaders(void);

        void addTexture(GuiTexture texture){
            textures.push_back(texture);
        }
        void turnOnOption(unsigned char val){
            options |= val;
        }
        void turnOffOption(unsigned char val){
            options &= ~val;
        }
        void toggleOption(unsigned char val){
            options ^= val;
        }
        //DEPRECATED
        void render(PointerRawModel);
        void render(PointerMaterialedModel);
        void renderObject(PointerEntity, std::vector<PointerPointLight>);

        const static unsigned char FLAG_TEXTURE         = 0x01; // hex for 0000 0001
        const static unsigned char FLAG_NORMAL_MAP      = 0x02; // hex for 0000 0010
        const static unsigned char FLAG_LIGHT           = 0x04; // hex for 0000 0100
        const static unsigned char FLAG_SPECULAR        = 0x08; // hex for 0000 1000
        const static unsigned char FLAG_FOG             = 0x10; // hex for 0001 0000
        const static unsigned char FLAG_ENVIRONMENTAL   = 0x20; // hex for 0010 0000
        const static unsigned char FLAG_WATER           = 0x40; // hex for 0100 0000
        const static unsigned char FLAG_SHADOW          = 0x80; // hex for 1000 0000

        void prepareRenderer(GLfloat red  = 0, GLfloat green  = 0, GLfloat blue  = 0, GLfloat alpha = 1) override;

    private:
        void setCamera(PointerCamera);
        int options = FLAG_TEXTURE | FLAG_NORMAL_MAP | FLAG_LIGHT | FLAG_SPECULAR | FLAG_FOG;
        Fbo multiFbo;
        Fbo fbo, fbo2, fbo3;
        PostProccessing pp;
        WaterFrameBuffer wf;

        std::map<std::string, PointerBasicShader> shaders;
        const PointLight * light = new PointLight(Vector3f(0, 0, 0), Vector3f(1, 1, 1));
        std::vector<GuiTexture> textures;
        //PRIVATE METHODS
};


#endif //GRAPHICSPROJECT_RENDERER_H
