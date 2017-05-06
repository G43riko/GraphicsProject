//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_SKYMASTER_H
#define GRAPHICSPROJECT_SKYMASTER_H

#include <src/rendering/material/CubeTexture.h>
#include <src/rendering/RenderUtil.h>
#include <src/rendering/shader/SkyBoxShader.h>

#define SIZE 500
#define SKYBOX_VERTICES {-SIZE,  SIZE, -SIZE, -SIZE, -SIZE, -SIZE,  SIZE, -SIZE, -SIZE,  SIZE, -SIZE, -SIZE,  SIZE,  SIZE, -SIZE, -SIZE,  SIZE, -SIZE,\
                         -SIZE, -SIZE,  SIZE, -SIZE, -SIZE, -SIZE, -SIZE,  SIZE, -SIZE, -SIZE,  SIZE, -SIZE, -SIZE,  SIZE,  SIZE, -SIZE, -SIZE,  SIZE,\
                          SIZE, -SIZE, -SIZE,  SIZE, -SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE, -SIZE,  SIZE, -SIZE, -SIZE,\
                         -SIZE, -SIZE,  SIZE, -SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE, -SIZE,  SIZE, -SIZE, -SIZE,  SIZE,\
                         -SIZE,  SIZE, -SIZE,  SIZE,  SIZE, -SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  SIZE, -SIZE,  SIZE,  SIZE, -SIZE,  SIZE, -SIZE,\
                         -SIZE, -SIZE, -SIZE, -SIZE, -SIZE,  SIZE,  SIZE, -SIZE, -SIZE,  SIZE, -SIZE, -SIZE, -SIZE, -SIZE,  SIZE,  SIZE, -SIZE,  SIZE}

class SkyBoxMaster {
private:
    BasicShader * shader = new SkyBoxShader();
    PointerRawModel model;
public:
    inline void renderSky(const PointerCubeTexture sky, const PointerCamera camera){
        if(IS_NULL(sky)){
            return;
        }
        shader -> bind();
        shader -> updateUniform4m(VIEW_MATRIX, camera -> getViewMatrix());

        RenderUtil::prepareModel(model, 1);
        sky -> bind();
        glDrawArrays(GL_TRIANGLES, 0, model -> getVertexCount());
        RenderUtil::finishRender(1);
    }
    inline void cleanUp(void){
        shader -> cleanUp();
        delete shader;
    };
    inline SkyBoxMaster(const PointerCamera camera, Loader loader){
        RenderUtil::updateProjectionMatrix(shader, camera);
        model = loader.loadToVao(SKYBOX_VERTICES, 3);
    };
    inline BasicShader * getShader(void) const{ return shader; };
};


#endif //GRAPHICSPROJECT_SKYMASTER_H
