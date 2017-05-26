//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_RENDERUTIL_H
#define GRAPHICSPROJECT_RENDERUTIL_H


#include "Camera.h"
#include "model/Entity.h"
#include "shader/BasicShader.h"

class RenderUtil {
public:
    const static u_char FLAG_TEXTURE         = 0x01; // hex for 0000 0001
    const static u_char FLAG_NORMAL_MAP      = 0x02; // hex for 0000 0010
    const static u_char FLAG_LIGHT           = 0x04; // hex for 0000 0100
    const static u_char FLAG_SPECULAR        = 0x08; // hex for 0000 1000
    const static u_char FLAG_FOG             = 0x10; // hex for 0001 0000
    const static u_char FLAG_ENVIRONMENTAL   = 0x20; // hex for 0010 0000
    const static u_char FLAG_WATER           = 0x40; // hex for 0100 0000
    const static u_char FLAG_SHADOW          = 0x80; // hex for 1000 0000

    inline static void prepareModel(const PointerRawModel model, const uint numberOfAttributes){//DEPRECATED 26.5.2017
        prepareModel(*model, numberOfAttributes);
    }
    inline static void prepareModel(const RawModel& model, const uint numberOfAttributes){
        glBindVertexArray(model.getVaoID());
        LOOP_U(numberOfAttributes, i){
            glEnableVertexAttribArray(i);
        }
    }

    inline static void prepareMaterial(const PointerMaterial material,
                                       const PointerBasicShader shader,
                                       const int options){//DEPRECATED 26.5.2017
        prepareMaterial(material, shader, options);
    }

    inline static void prepareMaterial(const PointerMaterial material, BasicShader * shader, const int options){
        if(IS_NOT_NULL(shader) && IS_NOT_NULL(material)){
            if(options & FLAG_SPECULAR){
                shader -> updateUniformf(UNIFORM_SHINE_DUMPER, material -> getShineDumper());
                shader -> updateUniformf(UNIFORM_REFLECTIVITY, material -> getReflectivity());
            }
            shader -> connectTextures();

            material -> getDiffuse() -> bind(GL_TEXTURE0);

            if(options & FLAG_ENVIRONMENTAL){
                if(material -> hasEnvironmentalMap())
                    material -> getEnvironmentalMap() -> bind(GL_TEXTURE1);
            }

            if(options & FLAG_NORMAL_MAP){
                PointerTexture2D normal = material -> getNormal();
                if(normal)
                    normal -> bind(GL_TEXTURE1);
            }
        }
    }

    inline static void finishRender(const GLuint numberOfAttributes){
        LOOP_U(numberOfAttributes, i){
            glDisableVertexAttribArray(i);
        }

        glBindVertexArray(0);
    }

    inline static void updateLightUniforms(const PointerPointLight light,
                                           const PointerBasicShader shader,
                                           const PointerCamera camera,
                                           const long unsigned int index,
                                           const bool eyeSpace = true){
        const Vector3f position = eyeSpace ? getEyeSpacePosition(light->getPosition(), camera -> getViewMatrix()) : light->getPosition();
        const std::string positionName = eyeSpace ? "lightPositionEyeSpace" : "lightPosition";
        shader -> updateUniform3f(positionName + "[" + std::to_string(index) + "]", position);
        shader -> updateUniform3f("lightColor[" + std::to_string(index) + "]", light->getDiffuseColor());
        shader -> updateUniform3f("attenuation[" + std::to_string(index) + "]", light -> getAttenuation());
    }

    inline static void updateLightUniforms(const PointerPointLight light,
                                           BasicShader * shader,
                                           const PointerCamera camera,
                                           const long unsigned int index,
                                           const bool eyeSpace = true){
        const Vector3f position = eyeSpace ? getEyeSpacePosition(light -> getPosition(), camera -> getViewMatrix()) : light->getPosition();
        const std::string positionName = eyeSpace ? "lightPositionEyeSpace" : "lightPosition";
        shader -> updateUniform3f(positionName + "[" + std::to_string(index) + "]", position);
        shader -> updateUniform3f("lightColor[" + std::to_string(index) + "]", light->getDiffuseColor());
        shader -> updateUniform3f("attenuation[" + std::to_string(index) + "]", light -> getAttenuation());
    }


    inline static Vector3f getEyeSpacePosition(const Vector3f& position , const Matrix4f& view){
        return Vector3f(view.m00 * position.x + view.m01 * position.y + view.m02 * position.z + view.m03,
                        view.m10 * position.x + view.m11 * position.y + view.m12 * position.z + view.m13,
                        view.m20 * position.x + view.m21 * position.y + view.m22 * position.z + view.m23);
    }

    inline static void updateProjectionMatrix(BasicShader& shader, const PointerCamera camera) {
        shader.bind();
        shader.updateUniform4m(UNIFORM_PROJECTION_MATRIX, camera -> getProjectionMatrix());
    }


};

#endif //GRAPHICSPROJECT_RENDERUTIL_H
