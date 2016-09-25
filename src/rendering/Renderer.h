//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RENDERER_H
#define GRAPHICSPROJECT_RENDERER_H


#include "model/RawModel.h"
#include "model/MaterialedModel.h"
#include "model/Entity.h"
#include <iostream>
#include "Camera.h"
#include "shader/BasicShader.cpp"
#include <glm/mat4x4.hpp>
#include "../utils/Maths.h"

class Renderer {
    public:
        Renderer(BasicShader *);
        void render(RawModel *);
        void render(MaterialedModel *);
        void render(Entity *, BasicShader *);
        void prepare(GLfloat, GLfloat, GLfloat, GLfloat);
    private:
        Camera * actualCamera;
        void prepareModel(RawModel *, GLuint);
        void prepareMaterial(Material *);

        void finishRender(GLuint);
};


#endif //GRAPHICSPROJECT_RENDERER_H
