 //
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_TEXTURE2D_H
#define GRAPHICSPROJECT_TEXTURE2D_H

#include <src/utils/Const.h>
#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <vector>

class TextureData{
    private:
        GLuint id;
        GLenum type;
    public:
        TextureData(GLuint id, GLenum type);
        void setFilter(GLint filter);//GL_LINEAR, GL_NEAREST
        void setWrap(GLint wrap);
        void setMipmapping(void);

        void bind(void);
        void bind(GLuint num);
        void cleanUp(void);
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
        std::string getTitle(void);
        int getWidth(void);
        int getHeight(void);
        void cleanUp(void);
};
typedef std::shared_ptr<Texture2D> PointerTexture2D;
//PointerTexture2D initTexture2D(std::string, std::vector<unsigned char>, int, int);
PointerTexture2D createTexture2D(std::string, GLuint, int, int);
PointerTexture2D createTexture2D(GLuint);


#endif //GRAPHICSPROJECT_TEXTURE2D_H
