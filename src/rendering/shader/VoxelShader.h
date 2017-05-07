//
// Created by gabriel on 16.4.2017.
//

#include "BasicShader.h"

class VoxelShader : public BasicShader{
public:
    VoxelShader() : BasicShader("VoxelShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "Position");
        this -> bindAttribute(1, "Texture");
        this -> bindAttribute(2, "Normal");
    };
    void setAllUniforms(void){
        setUniform("color");
        setUniform("colorMatrix");
        setUniform("viewMatrix");
        setUniform("cameraPosition");
        setUniform("projectionMatrix");
        setUniform("transformationMatrix");
        setUniform("material");

        for(int i=0 ; i<MAX_LIGHTS ; i++){
            this -> setUniform("lightPosition[" + std::to_string(i) + "]");
            this -> setUniform("lightColor[" + std::to_string(i)+ "]");
            this -> setUniform("attenuation[" + std::to_string(i)+ "]");

            this -> setUniform("lightData[" + std::to_string(i)+ "].type");
            this -> setUniform("lightData[" + std::to_string(i)+ "].position");
            this -> setUniform("lightData[" + std::to_string(i)+ "].diffuseColor");
            this -> setUniform("lightData[" + std::to_string(i)+ "].specularColor");
            this -> setUniform("lightData[" + std::to_string(i)+ "].attenuation");
            this -> setUniform("lightData[" + std::to_string(i)+ "].direction");
            this -> setUniform("lightData[" + std::to_string(i)+ "].cutOff");
            this -> setUniform("lightData[" + std::to_string(i)+ "].outerCutOff");
        }
        this -> setUniform("sun.type");
        this -> setUniform("sun.cutOff");
        this -> setUniform("sun.position");
        this -> setUniform("sun.direction");
        this -> setUniform("sun.attenuation");
        this -> setUniform("sun.outerCutOff");
        this -> setUniform("sun.diffuseColor");
        this -> setUniform("sun.specularColor");

        setUniform("material.specularColor");
        setUniform("material.ambientColor");
        setUniform("material.reflectivity");
        setUniform("material.diffuseColor");
        setUniform("material.shineDumper");
    }
};