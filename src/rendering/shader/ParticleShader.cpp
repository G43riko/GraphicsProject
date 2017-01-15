//
// Created by gabriel on 18.11.2016.
//

#include "BasicShader.h"

class ParticleShader : public BasicShader{
public:
    ParticleShader() : BasicShader("ParticleShader"){
        compileShader();
    }

    void setAllAttributes(void){
        this -> bindAttribute(0, "position");

    }
    void connectTextures(void){
        updateUniformi("particleTexture", 0);
    }
    void setAllUniforms(void){
        this -> setUniform("particleTexture");
        this -> setUniform("projectionMatrix");
        this -> setUniform("modelViewMatrix");

        this -> setUniform("textOffset1");
        this -> setUniform("textOffset2");
        this -> setUniform("textCoordInfo");
    }
};