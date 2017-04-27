//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_GUIMASTER_H
#define GRAPHICSPROJECT_GUIMASTER_H


#include <vector>
#include "GuiTexture.h"
#include "../../rendering/RenderUtil.h"
#include <src/rendering/shader/GuiShader.h>

#define GUI_VERTICES {-1,  1, -1, -1,  1,  1,  1, -1}

class GuiMaster {
private:
    BasicShader  * shader = new GuiShader();
    PointerRawModel model;
public:
    inline void renderGui(std::vector<GuiTexture> textures){
        if(textures.empty()){
            return;
        }
        shader -> bind();
        RenderUtil::prepareModel(model, 1);

        glEnable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for(unsigned int i=0 ; i<textures.size() ; i++){
            glBindTexture(GL_TEXTURE_2D, textures[i].getTexture());
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Maths::createTransformationMatrix(textures[i].getPosition(), textures[i].getScale()));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());
        }
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        RenderUtil::finishRender(1);
    }
    inline GuiMaster(PointerCamera camera, Loader loader){
        model = loader.loadToVao(GUI_VERTICES, 2);
    };
    inline void cleanUp(void){
        shader -> cleanUp();
        delete shader;
    };
    inline BasicShader * getShader(void) const{
        return shader;
    };
};


#endif //GRAPHICSPROJECT_GUIMASTER_H
