 //
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_TEXTURE2D_H
#define GRAPHICSPROJECT_TEXTURE2D_H

#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <vector>

class TextureData{
    private:
        GLuint id;
        GLenum type;
    public:
        TextureData(GLuint id, GLenum type){
            this -> id = id;
            this -> type = type;
        }
        void setFilter(GLint filter){//GL_LINEAR, GL_NEAREST
            glTexParameteri(type, GL_TEXTURE_MAG_FILTER, filter);
            glTexParameteri(type, GL_TEXTURE_MIN_FILTER, filter);
        }
        void setWrap(GLint wrap){
            glTexParameteri(type, GL_TEXTURE_WRAP_S, wrap);
            glTexParameteri(type, GL_TEXTURE_WRAP_T, wrap);
        }
        void setMipmapping(){
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.4f);
        }

        void bind(){
            glBindTexture(type, id);
        }

        void bind(GLuint num){
            glActiveTexture(num);
            bind();
        }
        void cleanUp(void){
            glDeleteTextures(1, &id);
        }
};

class Texture2D {
    private:
        GLuint textureID;
        int width;
        int height;
        std::string title;
    public:
        Texture2D(GLuint);
        Texture2D(std::string, GLuint, int, int);
        GLuint getTextureID(void);
        void bind(void);
        void bind(GLuint);
        int getWidth(void){
            return width;
        };
        int getHeight(void){
            return height;
        };
        GLuint getId(void){
            return textureID;
        };
        void cleanUp(void){
            glDeleteTextures(1, &textureID);
        }
};
typedef std::shared_ptr<Texture2D> PointerTexture2D;
PointerTexture2D initTexture2D(std::string, std::vector<unsigned char>, int, int);
PointerTexture2D createTexture2D(std::string, GLuint, int, int);
PointerTexture2D createTexture2D(GLuint);


#endif //GRAPHICSPROJECT_TEXTURE2D_H
