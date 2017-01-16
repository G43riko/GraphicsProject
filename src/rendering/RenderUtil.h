//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_RENDERUTIL_H
#define GRAPHICSPROJECT_RENDERUTIL_H


#include "src/components/lights/PointLight.h"
#include "Camera.h"
#include "model/Entity.h"
#include "shader/BasicShader.h"

class RenderUtil {
public:
    static Vector3f getEyeSpacePosition(PointerPointLight, glm::mat4);
    static void prepareModel(PointerRawModel, GLuint);
    static void prepareMaterial(PointerMaterial material, PointerBasicShader shader, int options);
    static void prepareMaterial(PointerMaterial material, BasicShader * shader, int options);
    static void finishRender(GLuint);
    static void updateLightUniforms(PointerPointLight light, PointerBasicShader shader, PointerCamera camera, int index, bool eyeSpace = true);
    static void updateLightUniforms(PointerPointLight light, BasicShader *shader, PointerCamera camera, int index, bool eyeSpace = true);

    inline static void updateProjectionMatrix(BasicShader * shader,  PointerCamera camera){
        shader -> bind();
        shader -> updateUniform4m("projectionMatrix", camera -> getProjectionMatrix());
    }
};


#endif //GRAPHICSPROJECT_RENDERUTIL_H
