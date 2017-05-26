//
// Created by gabriel on 1.11.2016.
//

#ifndef GAMEENGINE_HORIZONTAL_BLUR_SHADER_H
#define GAMEENGINE_HORIZONTAL_BLUR_SHADER_H

#include "BasicShader.h"

class HorizontalBlurShader : public BasicShader{
    public:
        HorizontalBlurShader() : BasicShader("HorizontalBlurShader", "BlurShader"){
            compileShader();
        };

        void setAllAttributes(void){
            this -> bindAttribute(0, "Position");
            //this -> bindAttribute(1, "Texture");

        };
        void setAllUniforms(void){
            this -> setUniform("targetWidth");
        }
};

#endif //GAMEENGINE_HORIZONTAL_BLUR_SHADER_H