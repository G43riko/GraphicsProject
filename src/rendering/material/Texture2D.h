//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_TEXTURE2D_H
#define GRAPHICSPROJECT_TEXTURE2D_H

#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <vector>

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
