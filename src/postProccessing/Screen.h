//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_SCREEN_H
#define GRAPHICSPROJECT_SCREEN_H


#include <../rendering/material/Texture2D.h>
#include <../utils/Vectors.h>
#include <../utils/Loader.h>
#include "ToFrameBufferRendering.h"
#include "../rendering/Renderer.h"
#include "Fbo.h"


class Screen {
private:
    static PointerRawModel MODEL;
    static std::vector<float> POINTS;
    PointerTexture2D texture;

    Vector2f * position;
    Vector2f * scale;
    ToFrameBufferRendering * frameRenderer;

    //CONSTRUCTORS

public:
    Screen(int, int, Loader *);

    //OTHERS
/*
    void render(Renderer * renderer) {
        renderer -> renderScreen(this, nullptr);
    }
*/
    void cleanUp(){
        frameRenderer -> cleanUp();
    }

    void startRenderToScreen() {
        frameRenderer -> startRenderToFrameBuffer();
    }

    void stopRenderToScreen() {
        frameRenderer -> stopRenderToFrameBuffer();
    }

    //GETTERS
    glm::mat4 getTransformationMatrix() {return Maths::createTransformationMatrix(position, scale);}

    PointerRawModel getModel(){return MODEL;}
    PointerTexture2D getTexture() {return texture;}

    //SETTERS

    void setTexture(PointerTexture2D texture) {
        this -> texture = texture;
    }
};


#endif //GRAPHICSPROJECT_SCREEN_H
