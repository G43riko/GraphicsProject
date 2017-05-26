//
// Created by gabriel on 1.11.2016.
//

#ifndef GAMEENGINE_VERTICAL_BLUR_SHADER_H
#define GAMEENGINE_VERTICAL_BLUR_SHADER_H

#include "BasicShader.h"

class VerticalBlurShader : public BasicShader{
public:
    VerticalBlurShader() : BasicShader("VerticalBlurShader", "BlurShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "Position");
        //this -> bindAttribute(1, "Texture");

    };

    void setAllUniforms(void){
        this -> setUniform("targetHeight");
    }
};

#endif //GAMEENGINE_VERTICAL_BLUR_SHADER_H