//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RENDERER_H
#define GRAPHICSPROJECT_RENDERER_H


#include "model/RawModel.h"
#include "model/MaterialedModel.h"
#include "model/Entity.h"
#include "../entities/Light.h"
#include <iostream>
#include "Camera.h"
#include "shader/BasicShader.cpp"
#include <glm/mat4x4.hpp>
#include "../utils/Maths.h"
#include "../postProccessing/Screen.h"

class Screen;

class Renderer {
    public:
        void render(PointerRawModel);
        void render(PointerMaterialedModel);
        void renderEntity(PointerEntity);
        void renderObject(PointerEntity, std::vector<PointerLight>);
        void renderScreen(Screen *, int = 0);
        void setCamera(PointerCamera);
        void updateProjectionMatrix(PointerCamera, PointerBasicShader = nullptr);
        void prepare(GLfloat, GLfloat, GLfloat, GLfloat);
        void init3D(void);
        void addShader(std::string, PointerBasicShader);
    private:
        Vector3f * getEyeSpacePosition(Light * light, glm::mat4 viewMatrix){
            Vector3f * position = light -> position;
            glm::vec3 eyeSpacePos(position -> x, position ->y, position -> z);
            glm::mat4 res = glm::translate(viewMatrix, eyeSpacePos);
            glm::vec3 result(eyeSpacePos);
            return new Vector3f(result.x, result.y, result.z);
        };
        std::map<std::string, PointerBasicShader> shaders;
        Light * light = new Light(new Vector3f(0, 0, 0), new Vector3f(1, 1, 1));
        PointerCamera actualCamera = nullptr;
        void prepareModel(PointerRawModel, GLuint);
        void prepareMaterial(PointerMaterial);

        void finishRender(GLuint);
};


#endif //GRAPHICSPROJECT_RENDERER_H
