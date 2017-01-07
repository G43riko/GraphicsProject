//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_GUIMASTER_H
#define GRAPHICSPROJECT_GUIMASTER_H


#include <vector>
#include "GuiTexture.h"
#include "../../rendering/RenderUtil.h"

class GuiMaster {
private:
    PointerBasicShader shader;
    RenderUtil * utils;
public:
    void renderGui(std::vector<GuiTexture> textures, PointerRawModel model);
    GuiMaster(RenderUtil * utils, PointerBasicShader shader) : shader(shader), utils(utils){}
};


#endif //GRAPHICSPROJECT_GUIMASTER_H
