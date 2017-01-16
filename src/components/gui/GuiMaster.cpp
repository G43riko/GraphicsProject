//
// Created by gabriel on 7.1.2017.
//

#include "GuiMaster.h"

void GuiMaster::renderGui(std::vector<GuiTexture> textures){
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
        shader -> updateUniform4m("transformationMatrix", Maths::createTransformationMatrix(textures[i].getPosition(), textures[i].getScale()));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    RenderUtil::finishRender(1);
}