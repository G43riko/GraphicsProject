//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_CONSTRASTSHADER_H
#define GRAPHICSPROJECT_CONSTRASTSHADER_H


#include <src/rendering/shader/BasicShader.h>

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


#endif //GRAPHICSPROJECT_CONSTRASTSHADER_H
