//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_CONTRASTCHANGER_H
#define GRAPHICSPROJECT_CONTRASTCHANGER_H


#include "ImageRenderer.h"
#include "ContrastShader.h"

class ContrastChanger {
    private:
        ImageRenderer * renderer;
        ContrastShader * shader;
    public:
        ContrastChanger(int width, int height){
            shader = new ContrastShader();
            renderer = new ImageRenderer(width, height);
        }

        void render(int texture){
            shader -> bind();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            renderer -> renderQuad();
            shader -> unbind();
        }

        void  cleanUp(){
            renderer -> cleanUp();
            shader -> cleanUp();
        }
};


#endif //GRAPHICSPROJECT_CONTRASTCHANGER_H
