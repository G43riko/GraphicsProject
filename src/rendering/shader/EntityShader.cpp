//
// Created by gabriel on 2.10.2016.
//
#include "BasicShader.h"


class EntityShader : public BasicShader{
    public:
        EntityShader() : BasicShader("EntityShader"){};

        void setAllAttributes(void){
            this -> bindAttribute(0, "Position");
            this -> bindAttribute(1, "Texture");
            this -> bindAttribute(2, "Normal");

        };
        void setAllUniforms(void){
            this -> setUniform("projectionMatrix");
            this -> setUniform("viewMatrix");
            this -> setUniform("transformationMatrix");
        }
};