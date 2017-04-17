//
// Created by gabriel on 24.9.2016.
//

#include "Texture2D.h"

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
    this -> height  = height;
    this -> width   = width;
    this -> title   = title;
    textureID       = id;
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

std::string Texture2D::getTitle(void){
    return title;
}
int Texture2D::getWidth(void){
    return width;
}
int Texture2D::getHeight(void){
    return height;
}
void Texture2D::cleanUp(void){
    glDeleteTextures(1, &textureID);
}

/*
 * TextureData
 */

TextureData::TextureData(GLuint id, GLenum type){
this -> id      = id;
this -> type    = type;
}
void TextureData::setFilter(GLint filter){//GL_LINEAR, GL_NEAREST
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, filter);
}
void TextureData::setWrap(GLint wrap){
    glTexParameteri(type, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, wrap);
}
void TextureData::setMipmapping(void){
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.4f);
}

void TextureData::bind(void){
    glBindTexture(type, id);
}

void TextureData::bind(GLuint num){
    glActiveTexture(num);
    bind();
}
void TextureData::cleanUp(void){
    glDeleteTextures(1, &id);
}