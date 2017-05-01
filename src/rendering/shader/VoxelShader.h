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

        for(int i=0 ; i<MAX_LIGHTS ; i++){
            this -> setUniform("lightPosition[" + std::to_string(i) + "]");
            this -> setUniform("lightColor[" + std::to_string(i)+ "]");
            this -> setUniform("attenuation[" + std::to_string(i)+ "]");
        }
    }
};