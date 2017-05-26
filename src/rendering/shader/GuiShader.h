//
// Created by gabriel on 22.9.2016.
//

#ifndef GAMEENGINE_GUISHADER_H
#define GAMEENGINE_GUISHADER_H

#include "BasicShader.h"

class GuiShader : public BasicShader{
public:
    inline GuiShader() : BasicShader("GuiShader"){
        compileShader();
    };

    inline void setAllAttributes(void){
        this -> bindAttribute(0, "Position");
        //this -> bindAttribute(1, "Texture");

    };
    inline void setAllUniforms(void){
        //this -> setUniform("projectionMatrix");
        //this -> setUniform("viewMatrix");
        this -> setUniform("transformationMatrix");
    }
};

#endif //GAMEENGINE_GUISHADER_H