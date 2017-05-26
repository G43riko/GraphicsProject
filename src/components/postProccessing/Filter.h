//
// Created by gabriel on 1.11.2016.
//

#ifndef GRAPHICSPROJECT_FILTER_H
#define GRAPHICSPROJECT_FILTER_H


#include "ImageRenderer.h"
#include "src/rendering/shader/BasicShader.h"

class Filter {
    ImageRenderer renderer;
    const PointerBasicShader shader;
    uint targetHeight = 0;
    uint targetWidth = 0;
public:
    inline Filter(PointerBasicShader shader, const uint width = 0, const uint height = 0) : shader(shader){
        renderer = ImageRenderer(width, height);
    }

    inline PointerBasicShader getShader(void) const{
        return shader;
    }

    inline int getOutputTexture(void) const{
        return renderer.getOutputTexture();
    }


    inline void setTargetWidth(uint value){
        targetWidth = value;
    }
    inline void setTargetHeight(uint value){
        targetHeight = value;
    }

    inline void render(const int texture, const int texture2 = 0) const{
        shader -> bind();

        if(targetWidth != 0) {
            shader->updateUniformi("targetWidth", targetWidth);
        }

        if(targetHeight != 0) {
            shader->updateUniformi("targetHeight", targetHeight);
        }

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

    inline void cleanUp(void){
        renderer.cleanUp();
    }
};


#endif //GRAPHICSPROJECT_FILTER_H
