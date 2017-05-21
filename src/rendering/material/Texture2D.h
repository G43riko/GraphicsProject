 //
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_TEXTURE2D_H
#define GRAPHICSPROJECT_TEXTURE2D_H

#include <src/utils/GConst.h>
#include <src/utils/GTypes.h>
#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <vector>

class TextureData{
    const GLuint _id;
    const GLenum _type;
public:
    inline TextureData(const GLuint id, const GLenum type) :
            _id(id),
            _type(type){};

    inline void setFilter(const GLint filter) const{//GL_LINEAR, GL_NEAREST
        glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, filter);
        glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, filter);
    }
    inline void setWrap(const GLint wrap) const{
        glTexParameteri(_type, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(_type, GL_TEXTURE_WRAP_T, wrap);
    }
    inline void setMipmapping(void) const{
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.4f);
    }

    inline void bind(void) const{
        glBindTexture(_type, _id);
    }

    inline void bind(GLint num) const{
        glActiveTexture(num);
        bind();
    }
    inline void cleanUp(void) const{
        glDeleteTextures(1, &_id);
    }
};

class Texture2D {
    const GLuint _id;
    const GLint _width          = 0;
    const GLint _height         = 0;
    const std::string _title    = 0;

    inline Texture2D(const GLint i_id) : _id(i_id){};
    inline Texture2D(const std::string& title, const GLint id, const GLint width, const GLint height) :
            _id(id),
            _width(width),
            _height(height),
            _title(title){};
public:
    inline void cleanUp(void)const {glDeleteTextures(1, &_id);}
    inline void bind(void) const {glBindTexture(GL_TEXTURE_2D, _id);};
    inline void bind(const GLint num) const{glActiveTexture(num); bind();};

    //GETTERS
    inline int getWidth(void) const{return _width; };
    inline int getHeight(void) const{return _height; };
    inline GLuint getTextureID(void)const {return _id; };
    inline std::string getTitle(void) const{return _title; };

    inline static PointerTexture2D create(const std::string& title, const GLuint id, const int width, const int height){
        return PointerTexture2D(new Texture2D(title, id, width, height));
    }

    inline static PointerTexture2D create(const GLuint id){
        return PointerTexture2D(new Texture2D(id));
    }
};



#endif //GRAPHICSPROJECT_TEXTURE2D_H
