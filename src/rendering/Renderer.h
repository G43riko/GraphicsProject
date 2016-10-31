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
#include <glm/mat4x4.hpp>
#include "../utils/Maths.h"
#include "../postProccessing/Screen.h"

#include "shader/EntityShader.cpp"
#include "shader/PostFxShader.cpp"
#include "shader/ObjectShader.cpp"

class Screen;

class Renderer {
    public:
        Renderer(void);
        void render(PointerRawModel);
        void render(PointerMaterialedModel);
        void renderEntity(PointerEntity);
        void renderObject(PointerEntity, std::vector<PointerLight>);
        void renderScreen(Screen , int = 0);
        void setCamera(PointerCamera);
        void updateProjectionMatrix(PointerCamera, PointerBasicShader = nullptr);
        void prepare(GLfloat, GLfloat, GLfloat, GLfloat);
        void init3D(void);
        void addShader(std::string, PointerBasicShader);
        void cleanUp(void);
        void initShaders(void);
    private:
        Vector3f * getEyeSpacePosition(Light light, glm::mat4 view){
            PointerVector3f position = light.getPosition();
            glm::vec4 eye(position -> x, position ->y, position -> z, 1.0);
            float x = view[0][0] * eye.x + view[1][0] * eye.y + view[2][0] * eye.z + view[3][0] * eye.w;
            float y = view[0][1] * eye.x + view[1][1] * eye.y + view[2][1] * eye.z + view[3][1] * eye.w;
            float z = view[0][2] * eye.x + view[1][2] * eye.y + view[2][2] * eye.z + view[3][2] * eye.w;
            /*
            float x = view[0][0] * eye.x + view[0][1] * eye.y + view[0][2] * eye.z + view[0][3] * eye.w;
            float y = view[1][0] * eye.x + view[1][1] * eye.y + view[1][2] * eye.z + view[1][3] * eye.w;
            float z = view[2][0] * eye.x + view[2][1] * eye.y + view[2][2] * eye.z + view[2][3] * eye.w;
            */

            //float w = view[0][3] * eye.x + view[1][3] * eye.y + view[2][3] * eye.z + view[3][3] * eye.w;
            return new Vector3f(x, y, z);
        };
        std::map<std::string, PointerBasicShader> shaders;
        //Light * light = new Light(PointerVector3f(new Vector3f(0, 0, 0)), PointerVector3f(new Vector3f(1, 1, 1)));
        Light * light = new Light(createVector3f(0, 0, 0), createVector3f(1, 1, 1));
        PointerCamera actualCamera = nullptr;
        void prepareModel(PointerRawModel, GLuint);
        void prepareMaterial(PointerMaterial, PointerBasicShader);

        void finishRender(GLuint);
};


#endif //GRAPHICSPROJECT_RENDERER_H
