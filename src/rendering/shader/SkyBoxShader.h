//
// Created by gabriel on 1.11.2016.
//

#include "BasicShader.h"

class SkyBoxShader : public BasicShader{
public:
    SkyBoxShader() : BasicShader("SkyBoxShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "Position");

    };

    void setAllUniforms(void){
        this -> setUniform("projectionMatrix");
        this -> setUniform("viewMatrix");
    }
};