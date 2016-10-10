//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_TEXTURE2D_H
#define GRAPHICSPROJECT_TEXTURE2D_H

#include <GL/glew.h>
#include <iostream>
#include <memory>

class Texture2D {
    private:
        GLuint textureID;
    public:
        Texture2D(GLuint);
        GLuint getTextureID(void);
        void bind(void);
        void bind(GLuint);
};

typedef std::shared_ptr<Texture2D> PointerTexture2D;


#endif //GRAPHICSPROJECT_TEXTURE2D_H
