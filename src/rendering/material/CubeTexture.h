//
// Created by gabriel on 2.11.2016.
//

#ifndef GRAPHICSPROJECT_CUBETEXTURE_H
#define GRAPHICSPROJECT_CUBETEXTURE_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <memory>
#include "../static_libs/lodepng.h"

class CubeTexture;
typedef std::shared_ptr<CubeTexture> PointerCubeTexture;

class CubeTexture {
    private:
        GLuint textureID;
        std::string title;
    public:
        CubeTexture(std::string title, GLuint textureID){
            this -> textureID = textureID;
            this -> title = title;
        };
        GLuint getId(void){
            return textureID;
        };
        void cleanUp(void){
            glDeleteTextures(1, &textureID);
        }

    void bind(){
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    }

    void bind(GLuint num){
        glActiveTexture(num);
        bind();
    }
};



#endif //GRAPHICSPROJECT_CUBETEXTURE_H