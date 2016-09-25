//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_TEXTURE2D_H
#define GRAPHICSPROJECT_TEXTURE2D_H

#include <GL/glew.h>
#include <iostream>

class Texture2D {
    private:
        GLuint textureID;
    public:
        Texture2D(GLuint textureID){
            this -> textureID = textureID;
        }

        GLuint getTextureID(){
            return textureID;
        }

        void bind(){
            glBindTexture(GL_TEXTURE_2D, textureID);
        }

        void bind(GLuint num){
            glActiveTexture(num);
            bind();
        }
};


#endif //GRAPHICSPROJECT_TEXTURE2D_H
