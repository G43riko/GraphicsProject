//
// Created by gabriel on 2.11.2016.
//

#ifndef GRAPHICSPROJECT_CUBETEXTURE_H
#define GRAPHICSPROJECT_CUBETEXTURE_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <memory>
#include <src/static_libs/lodepng.h>

class CubeTexture {
    private:
        const GLuint textureID;
        const std::string title;
    public:
        inline CubeTexture(const std::string& title, const GLint& textureID) : textureID(textureID), title(title){};
        inline GLuint getId(void)const {return textureID;};
        inline void cleanUp(void) const {glDeleteTextures(1, &textureID);};
        inline void bind(void)const {glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);};
        inline void bind(const GLint& num) const{glActiveTexture(num); bind();};
};


inline PointerCubeTexture createCubeTexture(std::string title, GLuint textureID){
    return PointerCubeTexture(new CubeTexture(title, textureID));
}


#endif //GRAPHICSPROJECT_CUBETEXTURE_H
