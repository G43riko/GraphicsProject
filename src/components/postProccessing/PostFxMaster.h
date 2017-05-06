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
    PointerRawModel quad;
//    std::vector<Fbo> fbos;
//    PostProccessing postProcessing;

    inline void init(void){
        filters[FILTER::CONTRAST] = nullptr;
        filters[FILTER::VERTICAL_BLUR] = nullptr;
        filters[FILTER::HORIZONTAL_BLUR] = nullptr;
        filters[FILTER::COMBINED_FILTER] = nullptr;
    };
    inline void start(void) const{
        glBindVertexArray(quad -> getVaoID());
        glEnableVertexAttribArray(0);
        glDisable(GL_DEPTH_TEST);
    };

    inline void end(void) const{
        glEnable(GL_DEPTH_TEST);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    };
public:
    inline PostFxMaster(Loader loader, bool usingPostFx, int width, int height, int samples = 1) {
        if(samples == 1){
            mainFbo = new Fbo(width, height, FBO_DEPTH_TEXTURE);
        }
        else{
            mainFbo = new Fbo(width, height, FBO_DEPTH_RENDER_BUFFER, samples);
        }
        quad = loader.loadToVao(POST_FX_POSITIONS, 2);
        setUsingPostFx(usingPostFx);
        setContrastChanger();
    };

    inline void doPostProcessing(std::string fboName){
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

    inline void cleanUp(void){
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

    inline void addFbo(std::string name, int width, int height, int depthBufferType = FBO_DEPTH_TEXTURE){
        fbos[name] = new Fbo(width, height, depthBufferType);
    };

    inline void resolveToFbo(GLenum framebuffer, std::string fboName){
        mainFbo->resolveToFbo(framebuffer, *fbos[fboName]);
    };

    inline void startRender(void) const{
        if(usingPostFx){
            mainFbo -> bindFrameBuffer();
        }
    };
    inline void stopRender(void) const{
        mainFbo -> unbindFrameBuffer();
    };
    /**************GETTERS***********************/
    inline bool getUsingPostFx(void) const{
        return usingPostFx;
    };
    inline float getContrastValue(void) const{
        return contrast;
    };
    /**************SETTERS***********************/
    inline void setUsingPostFx(bool usingPostFx){
        this -> usingPostFx = usingPostFx;
    };
    inline void setContrastValue(float contrast){
        this -> contrast = contrast;
    };
    /**************FILTERS***********************/

    inline void setContrastChanger(void){
        filters[FILTER::CONTRAST] = new Filter(PointerBasicShader(new ContrastShader()));
    };
    inline void setHorizontalBlur(int width, int height, int targetWidth){
        filters[FILTER::HORIZONTAL_BLUR] = new Filter(PointerBasicShader(new HorizontalBlurShader()), width, height);
    };
    inline void setVerticalBlur(int width, int height, int targetHeight){
        filters[FILTER::VERTICAL_BLUR] = new Filter(PointerBasicShader(new VerticalBlurShader()), width, height);
    };
    inline void setCombinedFilter(void){
        filters[FILTER::COMBINED_FILTER] = new Filter(PointerBasicShader(new CombineShader()));
    };
};


#endif //GRAPHICSPROJECT_POSTFXMASTER_H
