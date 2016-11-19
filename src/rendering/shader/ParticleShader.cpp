//
// Created by gabriel on 18.11.2016.
//

#include "BasicShader.h"

class ParticleShader : public BasicShader{
public:
    ParticleShader() : BasicShader("ParticleShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "position");

    };
    void setAllUniforms(void){
        this -> setUniform("projectionMatrix");
        this -> setUniform("modelViewMatrix");
    }
};