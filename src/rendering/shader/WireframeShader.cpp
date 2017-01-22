//
// Created by gabriel on 7.1.2017.
//

#include "BasicShader.h"

class WireframeShader : public BasicShader{
public:
    WireframeShader() : BasicShader("WireframeShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "position");

    };
    void setAllUniforms(void){
        setUniform("viewMatrix");
        setUniform("projectionMatrix");
    }
};