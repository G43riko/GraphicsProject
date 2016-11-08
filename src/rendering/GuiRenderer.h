//
// Created by gabriel on 1.11.2016.
//

#ifndef GRAPHICSPROJECT_GUIRENDERER_H
#define GRAPHICSPROJECT_GUIRENDERER_H


#include "model/MaterialedModel.h"
#include "GuiTexture.h"

class GuiRenderer {
private:
    static PointerRawModel model = nullptr;
    const static std::vector<GLfloat> positions{-1, 1, -1, -1, 1, 1, 1, -1};
public:
    GuiRenderer(Loader loader){
        if(!model)
            model = loader.loadToVao(positions, 2);
    }

    void render(std::vector<GuiTexture> textures){
        glBindVertexArray(model -> getVaoID());
        glEnableVertexAttribArray(0);

        for(GuiTexture texture : textures){
            glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount())
        }

        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
};


#endif //GRAPHICSPROJECT_GUIRENDERER_H
