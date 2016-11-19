//
// Created by gabriel on 1.11.2016.
//

#ifndef GRAPHICSPROJECT_GUITEXTURE_H
#define GRAPHICSPROJECT_GUITEXTURE_H


#include <GL/glew.h>
#include "../utils/Vectors.h"

class GuiTexture {
private:
    GLuint texture;
    Vector2f position;
    Vector2f scale;
public:
    GuiTexture(GLuint texture, const Vector2f & position, const Vector2f & scale){
        this -> texture = texture;
        this -> position = position;
        this -> scale = scale;
    }
    GLuint getTexture(){
        return texture;
    }
    void setTexture(GLuint id){
        texture = id;
    }
    Vector2f getPosition(){
        return position;
    }
    Vector2f getScale(){
        return scale;
    }
};


#endif //GRAPHICSPROJECT_GUITEXTURE_H
