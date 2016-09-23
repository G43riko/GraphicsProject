//
// Created by gabriel on 22.9.2016.
//

#include "BasicShader.cpp"

class GuiShader : BasicShader{
    public:
        GuiShader() : BasicShader("GuiShader"){};

    void setAllAttributes(){
        this -> bindAttribute(0, "position");
    };
    void setAllUniforms(){
        this -> setUniform("ambientLight");
    }
};