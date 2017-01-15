//
// Created by gabriel on 7.1.2017.
//

#include "WaterMaster.h"

void WaterMaster::render(PointerCamera camera, std::vector<PointerPointLight> lights){
    shader -> bind();
    shader -> connectTextures();

    for(unsigned int i=0 ; i<lights.size() ; i++){
        utils -> updateLightUniforms(lights[i], shader, camera, i, false);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbo.getRefractionTexture());
    dudvMap -> bind(GL_TEXTURE2);
    normalMap -> bind(GL_TEXTURE3);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, fbo.getRefractionDepthTexture());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader -> updateUniformf("tiling", tiling);
    shader -> updateUniformf("shineDumper", shineDumper);
    shader -> updateUniformf("waveStrength", waveStrength);
    shader -> updateUniformf("reflectivity", reflectivity);


    shader -> updateUniformf("refractiveRation", refractiveRation);
    //waveStrength
    shader -> updateUniform3f("cameraPosition", camera -> position);
    shader -> updateUniformf("moveFactor", moveFactor);
    moveFactor = (float)fmod(moveFactor, 1);
    shader -> updateUniform4m("viewMatrix", camera -> getViewMatrix());

    utils -> prepareModel(quad, 1);

    Matrix4f modelMatrix = Maths::createTransformationMatrix(water.getX(), water.getHeight(), water.getZ(),
                                                             0, 0, 0,
                                                             water.getSize(), water.getSize(), water.getSize());
    shader -> updateUniform4m("modelMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, quad -> getVertexCount());

    glDisable(GL_BLEND);
    utils -> finishRender(1);
}