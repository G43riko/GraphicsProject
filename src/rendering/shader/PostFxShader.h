//
// Created by gabriel on 16.10.2016.
//

#include "BasicShader.h"

class PostFxShader : public BasicShader{
public:
    PostFxShader() : BasicShader("PostFxShader"){
        compileShader();
    };

    void setAllAttributes(void){
        this -> bindAttribute(0, "position");

    };
    void setAllUniforms(void){
        this -> setUniform("transformationMatrix");
        //this -> setUniform("mouseMove");
        //this -> setUniform("useCameraBlur");
        //this -> setUniform("useAntiAliasing");
        //this -> setUniform("typeOfView");

        this -> setUniform("greyscale");
        this -> setUniform("invert");
        this -> setUniform("contrast");
        this -> setUniform("levels");
    }
};