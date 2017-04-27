//
// Created by gabriel on 2.10.2016.
//
#include "BasicShader.h"


class EntityShader : public BasicShader{
    public:
        EntityShader() : BasicShader("EntityShader"){
            compileShader();
        };

        void connectTextures(void){
            updateUniformi("textureSampler", 0);
            updateUniformi("environmentalMap", 1);
            updateUniformi("shadowMap", 2);
        }

        void setAllAttributes(void){
            this -> bindAttribute(0, "Position");
            this -> bindAttribute(1, "Texture");
            this -> bindAttribute(2, "Normal");

        };
        void setAllUniforms(void){

            this -> setUniform("plane");

            this -> setUniform("projectionMatrix");
            this -> setUniform("viewMatrix");
            this -> setUniform("transformationMatrix");

            this -> setUniform("toShadowSpace");
            this -> setUniform("shadowMap");

            this -> setUniform("sun");

            for(int i=0 ; i<MAX_LIGHTS ; i++){
                this -> setUniform("lightPosition[" + std::to_string(i) + "]");
                this -> setUniform("lightColor[" + std::to_string(i)+ "]");
                this -> setUniform("attenuation[" + std::to_string(i)+ "]");
            }

            this -> setUniform("levels");

            this -> setUniform("environmentalMap");
            this -> setUniform("cameraPosition");
        }
};