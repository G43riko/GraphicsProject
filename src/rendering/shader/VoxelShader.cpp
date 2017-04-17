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
        this -> bindAttribute(0, "position");

    };
    void setAllUniforms(void){
        setUniform("color");
        setUniform("viewMatrix");
        setUniform("projectionMatrix");
        setUniform("transformationMatrix");
    }
};