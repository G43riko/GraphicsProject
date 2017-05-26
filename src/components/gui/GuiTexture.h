//
// Created by gabriel on 1.11.2016.
//

#ifndef GRAPHICSPROJECT_GUITEXTURE_H
#define GRAPHICSPROJECT_GUITEXTURE_H


#include <GL/glew.h>
#include "src/utils/math/objects/Vectors.h"

class GuiTexture {
private:
    const GLuint _id;
    Vector2f _position;
    Vector2f _scale;
public:
    inline GuiTexture(const GLuint id, const Vector2f & position, const Vector2f & scale) :
            _id(id),
            _position(position),
            _scale(scale){}

    inline Vector2f getPosition(void) const{return _position; }
    inline GLuint getTexture(void) const{return _id; }
    inline Vector2f getScale(void) const{return _scale; }

    inline void setPosition(Vector2f position){_position = position;}
//    inline void setTexture(GLuint i_id){ id = i_id; }
};


#endif //GRAPHICSPROJECT_GUITEXTURE_H
