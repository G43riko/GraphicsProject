//
// Created by gabriel on 15.10.2016.
//

#ifndef GAMEENGINE_CONTRASTSHADER_H
#define GAMEENGINE_CONTRASTSHADER_H

#include "BasicShader.h"

class ContrastShader : public BasicShader{
    public:
        ContrastShader() : BasicShader("ContrastShader"){
            compileShader();
        }
        void setAllAttributes(void){
            this -> bindAttribute(0, "position");
        };
        void setAllUniforms(void){
            this -> setUniform("contrast");
        }
};

#endif //GAMEENGINE_CONTRASTSHADER_H