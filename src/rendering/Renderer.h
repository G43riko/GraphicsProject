//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RENDERER_H
#define GRAPHICSPROJECT_RENDERER_H


#include "model/RawModel.h"
#include "model/MaterialedModel.h"
#include "model/Entity.h"
#include "../entities/Light.h";
#include <iostream>
#include "Camera.h"
#include "shader/BasicShader.cpp"
#include <glm/mat4x4.hpp>
#include "../utils/Maths.h"

class Renderer {
    public:
        Renderer(PointerBasicShader);
        void render(PointerRawModel);
        void render(PointerMaterialedModel);
        void render(PointerEntity, PointerBasicShader);
        void prepare(GLfloat, GLfloat, GLfloat, GLfloat);
    private:
        Light * light = new Light(new Vector3f(0, 0, 0), new Vector3f(1, 1, 1));
        Camera * actualCamera;
        void prepareModel(PointerRawModel, GLuint);
        void prepareMaterial(PointerMaterial);

        void finishRender(GLuint);
};


#endif //GRAPHICSPROJECT_RENDERER_H
