//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_IMAGERENDERER_H
#define GRAPHICSPROJECT_IMAGERENDERER_H

#include "Fbo.h"

class ImageRenderer {
private:
    Fbo * fbo = nullptr;
public:
    inline ImageRenderer(int width, int height) {
        this -> fbo = new Fbo(width, height, FBO_DEPTH_NONE);
    }
    inline ImageRenderer(void){

    }
    inline void renderQuad(void) const{
        if (fbo){
            fbo -> bindFrameBuffer();
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        if (fbo){
            fbo -> unbindFrameBuffer();
        }
    }

    inline int getOutputTexture(void) const{
        return fbo -> getColourTexture();
    }

    inline void cleanUp(void) {
        if (fbo){
            fbo -> cleanUp();
            delete fbo;
            fbo = nullptr;
        }
    }
};


#endif //GRAPHICSPROJECT_IMAGERENDERER_H
