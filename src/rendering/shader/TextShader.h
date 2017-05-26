//
// Created by gabriel on 23.5.2017.
//

#ifndef GAMEENGINE_TEXTSHADER_H
#define GAMEENGINE_TEXTSHADER_H

#include "BasicShader.h"

class TextShader : public BasicShader{
public:
    TextShader() : BasicShader("TextShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "vertex");

    };

    void setAllUniforms(void){
        this -> setUniform("projectionMatrix");
    }
};

#endif //GAMEENGINE_TEXTSHADER_H
