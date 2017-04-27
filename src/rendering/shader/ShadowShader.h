//
// Created by gabriel on 6.1.2017.
//
#include "BasicShader.h"


class ShadowShader : public BasicShader{
public:
    ShadowShader() : BasicShader("ShadowShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "in_position");

    };
    void setAllUniforms(void){
        this -> setUniform("mvpMatrix");
    }
};

