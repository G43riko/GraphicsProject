//
// Created by gabriel on 15.10.2016.
//

#include "BasicShader.h"

class CombineShader : public BasicShader{
public:
    CombineShader() : BasicShader("SimpleShader", "CombineShader"){
        compileShader();
    }
    void setAllAttributes(void){
        this -> bindAttribute(0, "Position");
    };
    void setAllUniforms(void){
        this -> setUniform("colourTexture");
        this -> setUniform("highlightTexture");
    }

    virtual void connectTextures(void){
        updateUniformi("colourTexture", 0);
        updateUniformi("highlightTexture", 1);
    };


};