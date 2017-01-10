//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_MASTER_H
#define GRAPHICSPROJECT_MASTER_H


#include <GL/glew.h>
#include <src/rendering/shader/BasicShader.h>
#include <src/rendering/RenderUtil.h>

class Master {
private:
    PointerBasicShader shader = nullptr;
    RenderUtil * utils = nullptr;
    GLenum polygonMode = GL_FILL;
public:
    void setPolygonMode(GLenum polygonMode){this -> polygonMode = polygonMode;}
    virtual void cleanUp(void){};

    void prepare(void){
        shader -> bind();
        glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    }

    void reset(void){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader -> unbind();
    }
};


#endif //GRAPHICSPROJECT_MASTER_H
