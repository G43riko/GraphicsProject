//
// Created by gabriel on 2.11.2016.
//

#include "CubeTexture.h"

PointerCubeTexture createCubeTexture(std::string title, GLuint textureID){
    return PointerCubeTexture(new CubeTexture(title, textureID));
}

CubeTexture::CubeTexture(std::string title, GLuint textureID){
    this -> textureID   = textureID;
    this -> title       = title;
}
GLuint CubeTexture::getId(void){
    return textureID;
}
void CubeTexture::cleanUp(void){
    glDeleteTextures(1, &textureID);
}
void CubeTexture::bind(void){
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

void CubeTexture::bind(GLuint num){
    glActiveTexture(num);
    bind();
}