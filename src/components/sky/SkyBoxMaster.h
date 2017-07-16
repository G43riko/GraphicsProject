//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_SKYMASTER_H
#define GRAPHICSPROJECT_SKYMASTER_H

#include <src/rendering/material/CubeTexture.h>
#include <src/rendering/RenderUtil.h>
#include <src/rendering/shader/SkyBoxShader.h>

#define SKYBOX_VERTICES {-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE, \
                         -SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE, \
                         -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                         -SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE, \
                         -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE, \
                         -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE, \
                          SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE}

class SkyBoxMaster {
    SkyBoxShader shader = SkyBoxShader();
    PointerRawModel model;
public:
    inline void renderSky(const CubeTexture& sky, BasicCamera& camera){
        shader.bind();
        shader.updateUniform4m(UNIFORM_VIEW_MATRIX, camera.getViewMatrix());

        RenderUtil::prepareModel(*model, 1);
        sky.bind();
        glDrawArrays(GL_TRIANGLES, 0, model -> getVertexCount());
        RenderUtil::finishRender(1);
    }
    inline void cleanUp(void){};
    inline SkyBoxMaster(BasicCamera& camera, Loader loader){
        RenderUtil::updateProjectionMatrix(shader, camera);
        model = loader.loadToVao(SKYBOX_VERTICES, 3);
    };
    inline BasicShader& getShader(void) { return shader; };
};


#endif //GRAPHICSPROJECT_SKYMASTER_H
