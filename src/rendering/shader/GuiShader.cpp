//
// Created by gabriel on 22.9.2016.
//

#include "BasicShader.cpp"

class GuiShader : public BasicShader{
    public:
        GuiShader() : BasicShader("GuiShader"){};

    void setAllAttributes(){
        this -> bindAttribute(0, "Position");
        this -> bindAttribute(1, "Texture");

    };
    void setAllUniforms(){
        this -> setUniform("projectionMatrix");
        this -> setUniform("viewMatrix");
        this -> setUniform("transformationMatrix");
    }
};