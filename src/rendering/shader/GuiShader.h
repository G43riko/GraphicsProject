//
// Created by gabriel on 22.9.2016.
//

#include "BasicShader.h"

class GuiShader : public BasicShader{
    public:
        GuiShader() : BasicShader("GuiShader"){
            compileShader();
        };

    void setAllAttributes(void){
        this -> bindAttribute(0, "Position");
        //this -> bindAttribute(1, "Texture");

    };
    void setAllUniforms(void){
        //this -> setUniform("projectionMatrix");
        //this -> setUniform("viewMatrix");
        this -> setUniform("transformationMatrix");
    }
};