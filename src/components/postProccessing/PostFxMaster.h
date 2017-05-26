//
// Created by gabriel on 16.1.2017.
//

#ifndef GRAPHICSPROJECT_POSTFXMASTER_H
#define GRAPHICSPROJECT_POSTFXMASTER_H


#include <src/utils/Loader.h>
#include "Fbo.h"
#include "Filter.h"
#include "src/rendering/shader/ContrastShader.h"
#include "src/rendering/shader/HorizontalBlurShader.h"
#include "src/rendering/shader/VerticalBlurShader.h"
#include "src/rendering/shader/CombineShader.h"


class PostFxMaster {
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
    inline PostFxMaster(Loader& loader,
                        const bool usingPostFx,
                        const int width,
                        const int height,
                        const int samples = 1) :
            quad(loader.loadToVao(POST_FX_POSITIONS, 2)){
        if(samples == 1){
            mainFbo = new Fbo(width, height, FBO_DEPTH_TEXTURE);
        }
        else{
            mainFbo = new Fbo(width, height, FBO_DEPTH_RENDER_BUFFER, samples);
        }
        setUsingPostFx(usingPostFx);

        //POZOR ak je filtru v konštruktore zadané rozlíšenie tak sa nebude renderovať na obrazovku ale vytvorý sa nové
        //FBO a do neho sa bude renderovať. Preto pri viacerých filtroch nesmie mať posledný zasané rozlíšenie!!!!!!!!!
        setContrastChanger();
    };

    /**
     * Funkcia spustí všetky filtre. Filter musí zobrať z predchádzajúceho FBO cez metodu getOutputTexture() a
     * prví filter musí zobrať FBO zo zoznamu FBOv cez fbos[fboName] -> getColourTexture()
     * @param fboName
     */
    inline void doPostProcessing(const std::string& fboName){
        start();

        filters[FILTER::CONTRAST] -> getShader() -> bind();
        filters[FILTER::CONTRAST] -> getShader() -> updateUniformf(UNIFORM_CONTRAST, contrast);
        filters[FILTER::CONTRAST] -> render(fbos[fboName] -> getColourTexture());

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

    inline void addFbo(const std::string& name,
                       const int width,
                       const int height,
                       const int depthBufferType = FBO_DEPTH_TEXTURE){
        fbos[name] = new Fbo(width, height, depthBufferType);
    };

    inline void resolveToFbo(const GLenum framebuffer, const std::string& fboName){
        mainFbo -> resolveToFbo(framebuffer, *fbos[fboName]);
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
    inline void setUsingPostFx(const bool usingPostFx){
        this -> usingPostFx = usingPostFx;
    };
    inline void setContrastValue(const float contrast){
        this -> contrast = contrast;
    };
    /**************FILTERS***********************/

    inline void setContrastChanger(const int width = 0, const int height = 0){
        filters[FILTER::CONTRAST] = new Filter(PointerBasicShader(new ContrastShader()), width, height);
    };
    inline void setHorizontalBlur(const int targetWidth, const int width = 0, const int height = 0){
        filters[FILTER::HORIZONTAL_BLUR] = new Filter(PointerBasicShader(new HorizontalBlurShader()), width, height);
    };
    inline void setVerticalBlur(const int targetHeight, const int width = 0, const int height = 0){
        filters[FILTER::VERTICAL_BLUR] = new Filter(PointerBasicShader(new VerticalBlurShader()), width, height);
    };
    inline void setCombinedFilter(void){
        filters[FILTER::COMBINED_FILTER] = new Filter(PointerBasicShader(new CombineShader()));
    };
};


#endif //GRAPHICSPROJECT_POSTFXMASTER_H
