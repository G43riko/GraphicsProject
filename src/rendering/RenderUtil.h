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
    Vector3f getEyeSpacePosition(PointerPointLight, glm::mat4);
    void prepareModel(PointerRawModel, GLuint);
    void prepareMaterial(PointerMaterial material, PointerBasicShader shader, int options);
    void finishRender(GLuint);

    void updateLightUniforms(PointerPointLight light, PointerBasicShader shader, PointerCamera camera, int index, bool eyeSpace = true);
};


#endif //GRAPHICSPROJECT_RENDERUTIL_H
