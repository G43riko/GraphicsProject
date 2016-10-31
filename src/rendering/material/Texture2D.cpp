//
// Created by gabriel on 24.9.2016.
//

#include "Texture2D.h"

PointerTexture2D initTexture2D(std::string title, std::vector<unsigned char> buffer, int width, int height){
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //TODO ako zistiť či ide o GL_RGBA alebo GL_RGB??
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());


    //MIPMAING
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.4f);

    return PointerTexture2D(new Texture2D(title, texture_id, width, height));
}

PointerTexture2D createTexture2D(std::string title, GLuint id, int width, int height){
    return PointerTexture2D(new Texture2D(title, id, width, height));
}
PointerTexture2D createTexture2D(GLuint id){
    return PointerTexture2D(new Texture2D(id));
}

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