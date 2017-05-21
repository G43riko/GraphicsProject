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
    const GLuint _textureID;
    const std::string _title;
    inline CubeTexture(const std::string& title, const GLint textureID) : _textureID(textureID), _title(title){};
public:
    inline GLuint getId(void) const{return _textureID;};
    inline std::string getTitle(void) const{return _title; }
    inline void cleanUp(void) const{glDeleteTextures(1, &_textureID);};
    inline void bind(void) const{glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);};
    inline void bind(const GLint num) const{glActiveTexture(num); bind();};

    inline static PointerCubeTexture create(const std::string& title, const GLuint textureID){
        return PointerCubeTexture(new CubeTexture(title, textureID));
    }

};




#endif //GRAPHICSPROJECT_CUBETEXTURE_H
