//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_POSTPROCCESSING_H
#define GRAPHICSPROJECT_POSTPROCCESSING_H


#include <src/rendering/model/RawModel.h>
#include <src/utils/Loader.h>
#include "ContrastChanger.h"

class PostProccessing {
    public:
        PostProccessing(Loader loader, int width, int height){
            quad = loader.loadToVAO(POSITIONS, 2);
            contrastChanger = new ContrastChanger(width, height);
        }

        void doPostProcessing(int colorTexture){
            start();
            contrastChanger -> render(colorTexture);
            end();
        }

        void cleanUp(){
            contrastChanger -> cleanUp();
        }
private:
    std::vector<float> POSITIONS{ -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    PointerRawModel quad;
    ContrastChanger * contrastChanger;

    void start(){
        glBindVertexArray(quad -> getVaoID());
        glEnableVertexAttribArray(0);
        glDisable(GL_DEPTH_TEST);
    }

    void end(){
        glEnable(GL_DEPTH_TEST);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
};


#endif //GRAPHICSPROJECT_POSTPROCCESSING_H
