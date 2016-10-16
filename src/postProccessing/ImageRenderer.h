//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_IMAGERENDERER_H
#define GRAPHICSPROJECT_IMAGERENDERER_H

#include "Fbo.h"

class ImageRenderer {
    private:
        Fbo * fbo;
    public:
        ImageRenderer(int width, int height) {
            this -> fbo = new Fbo(WindowManager::width, WindowManager::height, Fbo::NONE);
        }
        void renderQuad() {
            if (fbo)
                fbo -> bindFrameBuffer();

            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            if (fbo)
                fbo -> unbindFrameBuffer();
        }

        int getOutputTexture() {
            return fbo -> getColourTexture();
        }

        void cleanUp() {
            if (fbo)
                fbo -> cleanUp();
        }
};


#endif //GRAPHICSPROJECT_IMAGERENDERER_H
