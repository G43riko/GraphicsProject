//
// Created by gabriel on 1.11.2016.
//

#ifndef GRAPHICSPROJECT_GUITEXTURE_H
#define GRAPHICSPROJECT_GUITEXTURE_H


#include <GL/glew.h>
#include "src/utils/math/objects/Vectors.h"

class GuiTexture {
private:
    const GLuint id;
    Vector2f position;
    Vector2f scale;
public:
    inline GuiTexture(GLuint id, const Vector2f & position, const Vector2f & scale) : id(id), position(position), scale(scale){}

    inline Vector2f getPosition(void) const{return position; }
    inline GLuint getTexture(void) const{return id; }
    inline Vector2f getScale(void) const{return scale; }

//    inline void setTexture(GLuint i_id){ id = i_id; }
};


#endif //GRAPHICSPROJECT_GUITEXTURE_H
