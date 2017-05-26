//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_IMAGERENDERER_H
#define GRAPHICSPROJECT_IMAGERENDERER_H

#include "Fbo.h"

class ImageRenderer {
private:
    Fbo * _fbo = nullptr;
public:
    inline ImageRenderer(const uint width = 0, const uint height = 0) {
        if(width > 0 && height > 0){
            this -> _fbo = new Fbo(width, height, FBO_DEPTH_NONE);
        }
    }
//    inline ImageRenderer(void){
//
//    }
    inline void renderQuad(void) const{
        CHECK_AND_CALL(_fbo, bindFrameBuffer());

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        CHECK_AND_CALL(_fbo, unbindFrameBuffer());
    }

    inline int getOutputTexture(void) const{
        return _fbo -> getColourTexture();
    }

    inline void cleanUp(void) {
        CHECK_AND_CLEAR(_fbo);
    }
};


#endif //GRAPHICSPROJECT_IMAGERENDERER_H
