//
// Created by gabriel on 22.9.2016.
//

#include "BasicShader.cpp"

class EntityShader : BasicShader{
    EntityShader() : BasicShader("EntityShader"){};

    void setAllAttributes(){
        this -> bindAttribute(0, "position");
    };
    void setAllUniforms(){
        this -> setUniform("ambientLight");
    }
};