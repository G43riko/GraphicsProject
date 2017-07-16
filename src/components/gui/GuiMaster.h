//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_GUIMASTER_H
#define GRAPHICSPROJECT_GUIMASTER_H


#include <vector>
#include "GuiTexture.h"
#include "../../rendering/RenderUtil.h"
#include <src/rendering/shader/GuiShader.h>
#include <src/GUI/openGL/GuiManager.h>


class GuiMaster {
    GuiShader shader = GuiShader();
    const PointerRawModel model;
    GuiManager gui;

    inline void prepare(void) const{
        shader.bind();
        RenderUtil::prepareModel(*model, 1);

        glEnable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    inline void finish(void) const{
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        RenderUtil::finishRender(1);
    }
public:
    inline GuiMaster(Loader loader) :
            model(loader.loadToVao(GUI_VERTICES, 2)),
            gui(&shader, model){};

    inline void renderGui(std::vector<GuiTexture*> textures){
        if(textures.empty() && gui.isEmpty()){
            return;
        }
        prepare();
        ITERATE_VECTOR(textures, i){
            glBindTexture(GL_TEXTURE_2D, textures[i] -> getTexture());
            shader.updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX,
                                   Maths::createTransformationMatrix(textures[i] -> getPosition(),
                                                                     textures[i] -> getScale()));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());
        }
        gui.update(1.0f);
        gui.render();

        finish();
    }
    inline void cleanUp(void){};
    inline BasicShader& getShader(void){
        return shader;
    };
};


#endif //GRAPHICSPROJECT_GUIMASTER_H
