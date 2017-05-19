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
private:
    const GLuint id;
    const GLenum type;
public:
    inline TextureData(const GLuint& id, const GLenum& type) : id(id), type(type){};

    inline void setFilter(const GLint& filter) const{//GL_LINEAR, GL_NEAREST
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, filter);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, filter);
    }
    inline void setWrap(const GLint& wrap) const{
        glTexParameteri(type, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, wrap);
    }
    inline void setMipmapping(void) const{
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.4f);
    }

    inline void bind(void) const{
        glBindTexture(type, id);
    }

    inline void bind(const GLint& num) const{
        glActiveTexture(num);
        bind();
    }
    inline void cleanUp(void) const{
        glDeleteTextures(1, &id);
    }
};

class Texture2D {
    const GLuint id;
    const GLint width       = 0;
    const GLint height      = 0;
    const std::string title = 0;

    inline Texture2D(const GLint& i_id) : id(i_id){};
    inline Texture2D(const std::string& title, const GLint& id, const GLint& width, const GLint& height) : id(id), width(width), height(height), title(title){};
public:
    inline GLuint getTextureID(void)const {return id; };
    inline void bind(void) const {glBindTexture(GL_TEXTURE_2D, id);};
    inline void bind(const GLint& num) const{glActiveTexture(num); bind();};
    inline std::string getTitle(void) const{return title; };
    inline int getWidth(void) const{return width; };
    inline int getHeight(void) const{return height; };
    inline void cleanUp(void)const {glDeleteTextures(1, &id);}

    inline static PointerTexture2D create(std::string title, GLuint id, int width, int height){
        return PointerTexture2D(new Texture2D(title, id, width, height));
    }

    inline static PointerTexture2D create(GLuint id){
        return PointerTexture2D(new Texture2D(id));
    }
};



#endif //GRAPHICSPROJECT_TEXTURE2D_H
