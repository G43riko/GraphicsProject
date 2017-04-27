//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_GUIMASTER_H
#define GRAPHICSPROJECT_GUIMASTER_H


#include <vector>
#include "GuiTexture.h"
#include "../../rendering/RenderUtil.h"
#include <src/rendering/shader/GuiShader.cpp>

#define GUI_VERTICES {-1,  1, -1, -1,  1,  1,  1, -1}

class GuiMaster {
private:
    BasicShader  * shader = new GuiShader();
    PointerRawModel model;
public:
    void renderGui(std::vector<GuiTexture> textures);
    GuiMaster(PointerCamera camera, Loader loader){
        model = loader.loadToVao(GUI_VERTICES, 2);
    };
    void cleanUp(void){
        shader -> cleanUp();
        delete shader;
    };
    BasicShader * getShader(void){
        return shader;
    };
};


#endif //GRAPHICSPROJECT_GUIMASTER_H
