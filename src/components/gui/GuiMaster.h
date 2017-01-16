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
    PointerRawModel model;
public:
    void renderGui(std::vector<GuiTexture> textures);
    GuiMaster( PointerBasicShader shader, Loader loader) : shader(shader){
        std::vector<float> vertices = {-1, 1, -1, -1, 1, 1, 1, -1};
        model = loader.loadToVao(vertices, 2);
    };
    void cleanUp(void){};
};


#endif //GRAPHICSPROJECT_GUIMASTER_H
