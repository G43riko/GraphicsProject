//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_SCREEN_H
#define GRAPHICSPROJECT_SCREEN_H


#include <src/rendering/material/Texture2D.h>
#include <src/utils/Vectors.h>
#include <src/utils/Loader.h>
#include "ToFrameBufferRendering.h"
#include <src/rendering/shader/BasicShader.h>
#include "../../rendering/Renderer.h"
#include "Fbo.h"


class PostFx{

/*
 * blur
 * -offset X
 * -offset Y
 * -samples
 * -factor
 */

public:

private:
};

#define POINTS {-1, 1, -1, -1, 1, 1, 1, -1}

class Screen {
private:
    PointerRawModel MODEL = nullptr;
    PointerTexture2D texture;

    Vector2f position;
    Vector2f scale;
    ToFrameBufferRendering frameRenderer;

    //EFFECTS

    bool changed = true;
    Vector2f blurOffset = Vector2f(1, 1);
    float blurSamples = 3;
    float blurFactor = 0.5;
    float * filterMatrix;
    Vector2f filterOffset = Vector2f(1, 1);
    float filterFactor = 0.5;
    float filterBias = 0;
    bool greyscale = false;
    bool invert = false;
    float contrast = 0;//(0-1)(0=N)
    int levels = 0;
public:
    Screen(int width, int height, Loader loader) {
        MODEL = loader.loadToVao(POINTS, 2);
        frameRenderer = ToFrameBufferRendering(width, height);
        texture = frameRenderer.getTexture();
        position = Vector2f();
        scale = Vector2f(1, 1);

//    setGreyscale(true);
        //setInvert(true);
        //setContrast(1);
        //setLevels(0);

    }

    //OTHERS

    void cleanUp(){
        frameRenderer.cleanUp();
    }

    void startRenderToScreen() {
        frameRenderer.startRenderToFrameBuffer();
    }

    void stopRenderToScreen() {
        frameRenderer.stopRenderToFrameBuffer();
    }

    //GETTERS
    glm::mat4 getTransformationMatrix() {return Maths::createTransformationMatrix(position, scale);}

    PointerRawModel getModel(){return MODEL;}
    PointerTexture2D getTexture() {return texture;}

    //SETTERS

    void setTexture(PointerTexture2D texture) {
        this -> texture = texture;
    }
    //EFFECTS

    void setGreyscale(bool value = false){
        changed = true;
        greyscale = value;
    }

    void setInvert(bool value = false){
        changed = true;
        invert = value;
    }

    void setContrast(float value = 0){
        changed = true;
        contrast = value;
    }
    void setLevels(int value = 0){
        changed = true;
        levels = value;
    }
    bool isChanged(){
        return changed;
    }
    void setUniforms(PointerBasicShader shader){
        if(!changed)
            return;
        /*
        shader -> updateUniform2f("fitlerOffset", filterOffset);
        shader -> updateUniformf("filterFactor", filterFactor);
        shader -> updateUniformf("filterBias", filterBias);
        shader -> updateUniform4f("filterMatrix", *filterMatrix);
         */

        shader -> updateUniformb("greyscale", greyscale);
        shader -> updateUniformb("invert", invert);
        shader -> updateUniformf("contrast", contrast);
        shader -> updateUniformi("levels", levels);
        changed = false;
    }

};

#endif //GRAPHICSPROJECT_SCREEN_H
