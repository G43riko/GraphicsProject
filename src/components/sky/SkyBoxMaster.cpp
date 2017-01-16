//
// Created by gabriel on 7.1.2017.
//

#include "SkyBoxMaster.h"

void SkyBoxMaster::renderSky(PointerCubeTexture sky, PointerCamera camera){
    if(sky == nullptr){
        return;
    }
    shader -> bind();
    shader -> updateUniform4m("viewMatrix", camera -> getViewMatrix());
    RenderUtil::prepareModel(model, 1);
    sky -> bind();
    glDrawArrays(GL_TRIANGLES, 0, model -> getVertexCount());
    RenderUtil::finishRender(1);
}