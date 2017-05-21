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
    const static unsigned char FLAG_TEXTURE         = 0x01; // hex for 0000 0001
    const static unsigned char FLAG_NORMAL_MAP      = 0x02; // hex for 0000 0010
    const static unsigned char FLAG_LIGHT           = 0x04; // hex for 0000 0100
    const static unsigned char FLAG_SPECULAR        = 0x08; // hex for 0000 1000
    const static unsigned char FLAG_FOG             = 0x10; // hex for 0001 0000
    const static unsigned char FLAG_ENVIRONMENTAL   = 0x20; // hex for 0010 0000
    const static unsigned char FLAG_WATER           = 0x40; // hex for 0100 0000
    const static unsigned char FLAG_SHADOW          = 0x80; // hex for 1000 0000

    inline static void prepareModel(const PointerRawModel& model, const GLuint numberOfAttributes){
        glBindVertexArray(model -> getVaoID());
        for(GLuint i=0 ; i<=numberOfAttributes ; i++){
            glEnableVertexAttribArray(i);
        }
    }
    inline static void prepareModel(const RawModel& model, const GLuint numberOfAttributes){
        glBindVertexArray(model.getVaoID());
        for(GLuint i=0 ; i<=numberOfAttributes ; i++){
            glEnableVertexAttribArray(i);
        }
    }

    inline static void prepareMaterial(const PointerMaterial& material, const PointerBasicShader& shader, int options){
        prepareMaterial(*material, shader, options);
    }
    inline static void prepareMaterial(const Material& material, const PointerBasicShader& shader, int options){
        if(shader){
            if(options & FLAG_SPECULAR){
                shader -> updateUniformf("shineDumper", material.getShineDumper());
                shader -> updateUniformf("reflectivity", material.getReflectivity());
            }
            shader -> connectTextures();

            material.getDiffuse() -> bind(GL_TEXTURE0);

            if(options & FLAG_ENVIRONMENTAL){
                if(material.hasEnvironmentalMap()){
                    material.getEnvironmentalMap() -> bind(GL_TEXTURE1);
                }
            }

            if(options & FLAG_NORMAL_MAP){
                PointerTexture2D normal = material.getNormal();
                if(normal){
                    normal -> bind(GL_TEXTURE1);
                }
            }
        }
    }
    inline static void prepareMaterial(const PointerMaterial& material, BasicShader * shader, int options){
        if(IS_NOT_NULL(shader) && IS_NOT_NULL(material)){
            if(options & FLAG_SPECULAR){
                shader -> updateUniformf("shineDumper", material -> getShineDumper());
                shader -> updateUniformf("reflectivity", material -> getReflectivity());
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
        for(GLuint i=0 ; i<=numberOfAttributes ; i++)
            glDisableVertexAttribArray(i);

        glBindVertexArray(0);
    }

    inline static void updateLightUniforms(const PointerPointLight light,
                                           const PointerBasicShader shader,
                                           const PointerCamera camera,
                                           const int index,
                                           bool const eyeSpace = true){
        Vector3f position = eyeSpace ? getEyeSpacePosition(light->getPosition(), camera -> getViewMatrix()) : light->getPosition();
        std::string positionName = eyeSpace ? "lightPositionEyeSpace" : "lightPosition";
        shader -> updateUniform3f(positionName + "[" + std::to_string(index) + "]", position);
        shader -> updateUniform3f("lightColor[" + std::to_string(index) + "]", light->getDiffuseColor());
        shader -> updateUniform3f("attenuation[" + std::to_string(index) + "]", light -> getAttenuation());
    }

    inline static void updateLightUniforms(const PointerPointLight light,
                                           BasicShader * shader,
                                           const PointerCamera camera,
                                           const int index,
                                           const bool eyeSpace = true){
        Vector3f position = eyeSpace ? getEyeSpacePosition(light->getPosition(), camera -> getViewMatrix()) : light->getPosition();
        std::string positionName = eyeSpace ? "lightPositionEyeSpace" : "lightPosition";
        shader -> updateUniform3f(positionName + "[" + std::to_string(index) + "]", position);
        shader -> updateUniform3f("lightColor[" + std::to_string(index) + "]", light->getDiffuseColor());
        shader -> updateUniform3f("attenuation[" + std::to_string(index) + "]", light -> getAttenuation());
    }


//    inline static Vector3f getEyeSpacePosition(const Vector3f position , const glm::mat4 view){//DEPRECATED 20.5.2017
//        return Vector3f(view[0][0] * position.x + view[1][0] * position.y + view[2][0] * position.z + view[3][0],
//                        view[0][1] * position.x + view[1][1] * position.y + view[2][1] * position.z + view[3][1],
//                        view[0][2] * position.x + view[1][2] * position.y + view[2][2] * position.z + view[3][2]);
//    }
    inline static Vector3f getEyeSpacePosition(const Vector3f position , const Matrix4f view){
        return Vector3f(view.m00 * position.x + view.m01 * position.y + view.m02 * position.z + view.m03,
                        view.m10 * position.x + view.m11 * position.y + view.m12 * position.z + view.m13,
                        view.m20 * position.x + view.m21 * position.y + view.m22 * position.z + view.m23);
    }

    inline static void updateProjectionMatrix(BasicShader *shader, const PointerCamera camera) {
        shader -> bind();
        shader -> updateUniform4m(UNIFORM_PROJECTION_MATRIX, camera -> getProjectionMatrix());
    }


};

#endif //GRAPHICSPROJECT_RENDERUTIL_H
