//
// Created by gabriel on 7.1.2017.
//

#include "RenderUtil.h"
#include "Renderer.h"

void RenderUtil::prepareModel(PointerRawModel model, GLuint numberOfAttributes){
    glBindVertexArray(model -> getVaoID());
    for(GLuint i=0 ; i<=numberOfAttributes ; i++)
        glEnableVertexAttribArray(i);
}

void RenderUtil::prepareMaterial(PointerMaterial material, PointerBasicShader shader, int options){
    if(shader){
        if(options & Renderer::FLAG_SPECULAR){
            shader -> updateUniformf("shineDumper", material -> shineDumber);
            shader -> updateUniformf("reflectivity", material -> reflectivity);
        }
        shader -> connectTextures();

        material -> getDiffuse() -> bind(GL_TEXTURE0);

        if(options & Renderer::FLAG_ENVIRONMENTAL){
            if(material -> hasEnvironmentalMap())
                material -> getEnvironmentalMap().bind(1);
        }

        if(options & Renderer::FLAG_NORMAL_MAP){
            PointerTexture2D normal = material -> getNormal();
            if(normal)
                normal -> bind(GL_TEXTURE1);
        }
    }
}

void RenderUtil::finishRender(GLuint numberOfAttributes){
    for(GLuint i=0 ; i<=numberOfAttributes ; i++)
        glDisableVertexAttribArray(i);

    glBindVertexArray(0);
}

void RenderUtil::updateLightUniforms(PointerLight light, PointerBasicShader shader, PointerCamera camera, int index, bool eyeSpace){
    Vector3f position = eyeSpace ? getEyeSpacePosition(light, camera -> getViewMatrix()) : light->getPosition();
    std::string positionName = eyeSpace ? "lightPositionEyeSpace" : "lightPosition";
    shader -> updateUniform3f(positionName + "[" + std::to_string(index) + "]", position);
    shader -> updateUniform3f("lightColor[" + std::to_string(index) + "]", light -> getColor());
    shader -> updateUniform3f("attenuation[" + std::to_string(index) + "]", light -> getAttenuation());
}

Vector3f RenderUtil::getEyeSpacePosition(PointerLight light, glm::mat4 view){
    Vector3f position = light -> getPosition();

    float x = view[0][0] * position.x + view[1][0] * position.y + view[2][0] * position.z + view[3][0];
    float y = view[0][1] * position.x + view[1][1] * position.y + view[2][1] * position.z + view[3][1];
    float z = view[0][2] * position.x + view[1][2] * position.y + view[2][2] * position.z + view[3][2];

    return Vector3f(x, y, z);
}