//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RENDERER_H
#define GRAPHICSPROJECT_RENDERER_H


#include "model/RawModel.h"
#include "model/MaterialedModel.h"
#include "model/Entity.h"
#include "../components/lights/Light.h"
#include "../game/Scene.h"
#include <iostream>
#include "Camera.h"
#include <glm/mat4x4.hpp>
#include "../utils/Maths.h"
#include "../components/postProccessing/Screen.h"
#include "../components/gui/GuiTexture.h"
#include <glm/gtx/string_cast.hpp>

#include "../components/particles/Particle.h"
#include "shader/EntityShader.cpp"
#include "shader/PostFxShader.cpp"
#include "shader/ObjectShader.cpp"
#include "shader/GuiShader.cpp"
#include "shader/ParticleShader.cpp"
#include "shader/SkyBoxShader.cpp"
#include "shader/WaterShader.cpp"
#include "shader/ColorShader.cpp"
#include "shader/ShadowShader.cpp"
#include "../components/postProccessing/PostProccessing.h"
#include "../components/water/WaterFrameBuffer.h"
#include "../components/shadows/ShadowMaster.h"
#include "RenderUtil.h"
#include "../components/gui/GuiMaster.h"
#include "../components/sky/SkyBoxMaster.h"
#include "../components/particles/ParticleMaster.h"
#include "../components/entities/EntityMaster.h"
#include "../components/water/WaterMaster.h"

class Screen;
class Scene;

class Renderer {
    public:
        Renderer(Loader, int, int );
        //void renderGui(std::vector<GuiTexture> textures, PointerRawModel model);
        //void renderParticles(std::vector<Particle> particles, PointerRawModel model);
        void renderScene(Scene scene);
        //void renderShadows(PointerEntity entity, PointerLight sun);
        //void renderEntity(PointerEntity entity, std::vector<PointerLight> lights);
        void renderObjects(std::vector<PointerEntity>, std::vector<PointerLight>);
        void renderScreen(Screen screen);
        void updateProjectionMatrix(PointerCamera, PointerBasicShader = nullptr);
        void init3D(void);
        void update(float delta);
        void input(void);
        void addShader(std::string key, PointerBasicShader shader);
        void cleanUp(void);
        void initShaders(void);
        void addTexture(GuiTexture texture){
            textures.push_back(texture);
        }
        void setPostFx(bool val){
            usePostFx = val;
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
        void renderObject(PointerEntity, std::vector<PointerLight>);
        const static unsigned char FLAG_TEXTURE = 0x01; // hex for 0000 0001
        const static unsigned char FLAG_NORMAL_MAP = 0x02; // hex for 0000 0010
        const static unsigned char FLAG_LIGHT = 0x04; // hex for 0000 0100
        const static unsigned char FLAG_SPECULAR = 0x08; // hex for 0000 1000
        const static unsigned char FLAG_FOG = 0x10; // hex for 0001 0000
        const static unsigned char FLAG_ENVIRONMENTAL = 0x20; // hex for 0010 0000

        void prepareRenderer(GLfloat red  = 0, GLfloat green  = 0, GLfloat blue  = 0, GLfloat alpha = 1);
        PointerCamera getActualCamera(void){
            return actualCamera;
        }
        void setSun(PointerLight sun){
            this -> sun = sun;
        }
    private:
        WaterMaster * waterMaster;
        EntityMaster * entityMaster;
        ParticleMaster * particleMaster;
        GuiMaster * guiMaster;
        SkyBoxMaster * skyBoxMaster;
        ShadowMaster * shadowMaster = nullptr;
        void setCamera(PointerCamera);
        PointerLight sun = nullptr;
    //        const unsigned char option6 = 0x20; // hex for 0010 0000
    //        const unsigned char option7 = 0x40; // hex for 0100 0000
    //        const unsigned char option8 = 0x80; // hex for 1000 0000
        PointerCamera actualCamera = nullptr;
        unsigned char options = FLAG_TEXTURE | FLAG_NORMAL_MAP | FLAG_LIGHT | FLAG_SPECULAR | FLAG_FOG;
        Screen screen;
        RenderUtil utils;
        Fbo multiFbo;
        Fbo fbo, fbo2, fbo3;
        PostProccessing pp;
        WaterFrameBuffer wf;

        std::map<std::string, PointerBasicShader> shaders;
        Light * light = new Light(Vector3f(0, 0, 0), Vector3f(1, 1, 1));
        bool usePostFx = false;
        std::vector<GuiTexture> textures;
        //PRIVATE METHODS
};


#endif //GRAPHICSPROJECT_RENDERER_H
