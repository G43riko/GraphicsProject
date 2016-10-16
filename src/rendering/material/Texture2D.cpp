//
// Created by gabriel on 24.9.2016.
//

#include "Texture2D.h"

Texture2D::Texture2D(GLuint textureID){
    this -> textureID = textureID;
}

Texture2D::Texture2D(std::string title, GLuint id, int width, int height){
    this -> width = width;
    this -> height = height;
    this -> title = title;
    textureID = id;
}

GLuint Texture2D::getTextureID(void){
    return textureID;
}

void Texture2D::bind(){
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture2D::bind(GLuint num){
    glActiveTexture(num);
    bind();
}