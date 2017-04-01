//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_POSTPROCCESSING_H
#define GRAPHICSPROJECT_POSTPROCCESSING_H


#include <src/rendering/model/RawModel.h>
#include <src/utils/Loader.h>
#include "Filter.h"
#include "src/rendering/shader/ContrastShader.cpp"
#include "src/rendering/shader/HorizontalBlurShader.cpp"
#include "src/rendering/shader/VerticalBlurShader.cpp"
#include "src/rendering/shader/CombineShader.cpp"

class PostProccessing {
    public:
        PostProccessing(Loader loader){
            quad = loader.loadToVao(POSITIONS, 2);
            contrastChanger = new Filter(PointerBasicShader(new ContrastShader()));

            hBlur = new Filter(PointerBasicShader(new HorizontalBlurShader()), 160, 90);
            hBlur -> setTargetWidth(1600);

            vBlur = new Filter(PointerBasicShader(new VerticalBlurShader()), 160, 90);
            vBlur -> setTargetHeight(900);

            combineFilter = new Filter(PointerBasicShader(new CombineShader()));
        }

        void doPostProcessing(int colorTexture){
            start();
//            hBlur -> render(colorTexture);
//            vBlur -> render(hBlur->getOutputTexture());
            contrastChanger -> render(colorTexture);
//            contrastChanger -> render(vBlur->getOutputTexture());
//            combineFilter -> render(colorTexture, contrastChanger -> getOutputTexture());
            end();
        }

        void cleanUp(){
            if(contrastChanger){
                contrastChanger -> cleanUp();
                delete contrastChanger;
                contrastChanger = nullptr;
            }
            if(vBlur){
                vBlur -> cleanUp();
                delete vBlur;
                vBlur = nullptr;
            }
            if(hBlur){
                hBlur -> cleanUp();
                delete hBlur;
                hBlur = nullptr;
            }
            if(combineFilter){
                combineFilter -> cleanUp();
                delete combineFilter;
                combineFilter = nullptr;
            }
        }
private:
    std::vector<float> POSITIONS{ -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    PointerRawModel quad;
    Filter * contrastChanger;
    Filter * vBlur;
    Filter * hBlur;
    Filter * combineFilter;

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
