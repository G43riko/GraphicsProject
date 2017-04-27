//
// Created by gabriel on 16.1.2017.
//

#ifndef GRAPHICSPROJECT_POSTFXMASTER_H
#define GRAPHICSPROJECT_POSTFXMASTER_H


#include <src/utils/Loader.h>
#include "Fbo.h"
#include "PostProccessing.h"



class PostFxMaster {
private:
    enum FILTER{
        CONTRAST,
        VERTICAL_BLUR,
        HORIZONTAL_BLUR,
        COMBINED_FILTER,
    };

    float contrast = 0.7f;

    Fbo * mainFbo;
    bool usingPostFx;
    std::map<std::string, Fbo *> fbos;
    std::map<FILTER, Filter *> filters;

    std::vector<float> POSITIONS{ -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    PointerRawModel quad;
//    std::vector<Fbo> fbos;
//    PostProccessing postProcessing;

    void init(void){
        filters[FILTER::CONTRAST] = nullptr;
        filters[FILTER::VERTICAL_BLUR] = nullptr;
        filters[FILTER::HORIZONTAL_BLUR] = nullptr;
        filters[FILTER::COMBINED_FILTER] = nullptr;
    };
    void start(){
        glBindVertexArray(quad -> getVaoID());
        glEnableVertexAttribArray(0);
        glDisable(GL_DEPTH_TEST);
    };

    void end(){
        glEnable(GL_DEPTH_TEST);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    };
public:
    PostFxMaster(Loader loader, bool usingPostFx, int width, int height, int samples = 1) {
        if(samples == 1){
            mainFbo = new Fbo(width, height, FBO_DEPTH_TEXTURE);
        }
        else{
            mainFbo = new Fbo(width, height, FBO_DEPTH_RENDER_BUFFER, samples);
        }
        quad = loader.loadToVao(POSITIONS, 2);
        setUsingPostFx(usingPostFx);
        setContrastChanger();
    };

    void doPostProcessing(std::string fboName){
        start();
//            hBlur -> render(colorTexture);
//            vBlur -> render(hBlur->getOutputTexture());
        filters[FILTER::CONTRAST] ->getShader() -> bind();
        filters[FILTER::CONTRAST] ->getShader() -> updateUniformf("contrast", contrast);
        filters[FILTER::CONTRAST] -> render(fbos[fboName]->getColourTexture());
//            contrastChanger -> render(vBlur->getOutputTexture());
//            combineFilter -> render(colorTexture, contrastChanger -> getOutputTexture());
        end();
    }

    void cleanUp(void){
        for (auto it = fbos.begin(); it != fbos.end(); ++it){
            it -> second -> cleanUp();
            delete it -> second;
        }

        for (auto it = filters.begin(); it != filters.end(); ++it){
            it -> second -> cleanUp();
            delete it -> second;
        }
        mainFbo->cleanUp();
        delete mainFbo;
    };

    void addFbo(std::string name, int width, int height, int depthBufferType = FBO_DEPTH_TEXTURE){
        fbos[name] = new Fbo(width, height, depthBufferType);
    };

    void resolveToFbo(GLenum framebuffer, std::string fboName){
        mainFbo->resolveToFbo(framebuffer, *fbos[fboName]);
    };

    void startRender(void){
        if(usingPostFx){
            mainFbo -> bindFrameBuffer();
        }
    };
    void stopRender(void){
        mainFbo -> unbindFrameBuffer();
    };
    /**************GETTERS***********************/
    bool getUsingPostFx(void){
        return usingPostFx;
    };
    float getContrastValue(void){
        return contrast;
    };
    /**************SETTERS***********************/
    void setUsingPostFx(bool usingPostFx){
        this -> usingPostFx = usingPostFx;
    };
    void setContrastValue(float contrast){
        this -> contrast = contrast;
    };
    /**************FILTERS***********************/

    void setContrastChanger(void){
        filters[FILTER::CONTRAST] = new Filter(PointerBasicShader(new ContrastShader()));
    };
    void setHorizontalBlur(int width, int height, int targetWidth){
        filters[FILTER::HORIZONTAL_BLUR] = new Filter(PointerBasicShader(new HorizontalBlurShader()), width, height);
    };
    void setVerticalBlur(int width, int height, int targetHeight){
        filters[FILTER::VERTICAL_BLUR] = new Filter(PointerBasicShader(new VerticalBlurShader()), width, height);
    };
    void setCombinedFilter(void){
        filters[FILTER::COMBINED_FILTER] = new Filter(PointerBasicShader(new CombineShader()));
    };
};


#endif //GRAPHICSPROJECT_POSTFXMASTER_H
