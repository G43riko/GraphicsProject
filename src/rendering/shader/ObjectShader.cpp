//
// Created by gabriel on 16.10.2016.
//

#include "BasicShader.h"

class ObjectShader : public BasicShader{
public:
    ObjectShader() : BasicShader("ObjectShader"){
        compileShader();
    }
    void connectTextures(void){
        updateUniformi("textureSampler", 0);
        updateUniformi("normalSampler", 1);
    }
    void setAllAttributes(void){
        this -> bindAttribute(0, "Position");
        this -> bindAttribute(1, "Texture");
        this -> bindAttribute(2, "Normal");
        this -> bindAttribute(3, "Tangent");

    };
    void setAllUniforms(void){
        this -> setUniform("projectionMatrix");
        this -> setUniform("viewMatrix");
        this -> setUniform("transformationMatrix");

        this -> setUniform("textureSampler");
        this -> setUniform("normalSampler");

        for(int i=0 ; i<MAX_LIGHTS ; i++){
            this -> setUniform("lightPositionEyeSpace[" + std::to_string(i) + "]");
            this -> setUniform("lightColor[" + std::to_string(i)+ "]");
            this -> setUniform("attenuation[" + std::to_string(i)+ "]");
        }

        this -> setUniform("levels");
    }
};