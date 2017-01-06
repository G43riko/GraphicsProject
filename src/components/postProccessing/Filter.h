//
// Created by gabriel on 1.11.2016.
//

#ifndef GRAPHICSPROJECT_FILTER_H
#define GRAPHICSPROJECT_FILTER_H


#include "ImageRenderer.h"
#include "src/rendering/shader/BasicShader.h"

class Filter {
private:
    ImageRenderer renderer;
    PointerBasicShader shader;
    int targetHeight = 0;
    int targetWidth = 0;
public:
    Filter(PointerBasicShader shader){
        this -> shader = shader;
        renderer = ImageRenderer();
    }

    Filter(PointerBasicShader shader, int width, int height){
        this -> shader = shader;
        renderer = ImageRenderer(width, height);
    }

    PointerBasicShader getShader(){
        return shader;
    }

    int getOutputTexture(){
        return renderer.getOutputTexture();
    }


    void setTargetWidth(int value){
        targetWidth = value;
    }
    void setTargetHeight(int value){
        targetHeight = value;
    }

    void render(int texture, int texture2 = 0){
        shader -> bind();

        if(targetWidth != 0)
            shader -> updateUniformi("targetWidth", targetWidth);

        if(targetHeight != 0)
            shader -> updateUniformi("targetHeight", targetHeight);

        shader -> connectTextures();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        if(texture2 != 0){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
        }
        renderer.renderQuad();
        shader -> unbind();
    }

    void  cleanUp(){
        renderer.cleanUp();
        shader -> cleanUp();
    }
};


#endif //GRAPHICSPROJECT_FILTER_H
