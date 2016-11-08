//
// Created by gabriel on 2.10.2016.
//
#include "BasicShader.h"


class ColorShader : public BasicShader{
public:
    ColorShader() : BasicShader("ColorShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "Position");

    };
    void setAllUniforms(void){
        this -> setUniform("projectionMatrix");
        this -> setUniform("viewMatrix");
        this -> setUniform("transformationMatrix");

        this -> setUniform("color");
    }
};