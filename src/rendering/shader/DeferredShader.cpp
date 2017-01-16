//
// Created by gabriel on 14.1.2017.
//
#include "BasicShader.h"
#include <iostream>


class DeferredShader : public BasicShader{
public:
    DeferredShader() : BasicShader("DeferredShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "Position");
        this -> bindAttribute(1, "Texture");
        this -> bindAttribute(2, "Normal");

    };
    void setAllUniforms(void){

        this -> setUniform("cameraPosition");
        this -> setUniform("projectionMatrix");
        this -> setUniform("viewMatrix");
        this -> setUniform("transformationMatrix");
        for(int i=0 ; i<64 ; i++){
            this -> setUniform("samples[" + std::to_string(i) + "]");
        }

    }
};
