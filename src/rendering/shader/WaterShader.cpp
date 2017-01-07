//
// Created by gabriel on 7.1.2017.
//

#include "BasicShader.h"

class WaterShader : public BasicShader{
public:
    WaterShader() : BasicShader("WaterShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "position");

    };

    void connectTextures(void){
        updateUniformi("reflectionTexture", 0);
        updateUniformi("refractionTexture", 1);
        updateUniformi("dudvMap", 2);
        updateUniformi("normalMap", 3);
        updateUniformi("depthMap", 4);


    }
    void setAllUniforms(void){
        this -> setUniform("projectionMatrix");
        this -> setUniform("viewMatrix");
        this -> setUniform("modelMatrix");

        this -> setUniform("reflectionTexture");
        this -> setUniform("refractionTexture");
        this -> setUniform("dudvMap");
        this -> setUniform("normalMap");
        this -> setUniform("depthMap");


        for(int i=0 ; i<MAX_LIGHTS ; i++){
            this -> setUniform("lightPosition[" + std::to_string(i) + "]");
            this -> setUniform("lightColor[" + std::to_string(i)+ "]");
            //this -> setUniform("attenuation[" + std::to_string(i)+ "]");
        }


        this -> setUniform("moveFactor");

        this -> setUniform("cameraPosition");
    }
};