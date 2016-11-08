//
// Created by gabriel on 15.10.2016.
//

#include "BasicShader.h"

class ContrastShader : public BasicShader{
    public:
        ContrastShader() : BasicShader("ContrastShader"){
            compileShader();
        }
        void setAllAttributes(void){
            this -> bindAttribute(0, "position");
        };
        void setAllUniforms(void){}
};