//
// Created by gabriel on 2.11.2016.
//

#include "CubeTexture.h"

PointerCubeTexture createCubeTexture(std::string title, GLuint textureID){
    return PointerCubeTexture(new CubeTexture(title, textureID));
}