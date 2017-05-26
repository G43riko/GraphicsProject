//
// Created by gabriel on 23.5.2017.
//

#ifndef GAMEENGINE_TEXTLINE_H
#define GAMEENGINE_TEXTLINE_H

#include <src/utils/math/objects/Vectors.h>

class TextLine{
    const std::string _text;
    const float _x;
    const float _y;
    const float _scale;
    const Vector3f _color;
public:
    TextLine(std::string text, float x, float y, float scale = 1, Vector3f color = Vector3f()) :
            _text(text),
            _x(x),
            _y(y),
            _scale(scale),
            _color(color){}
    std::string getText(void) const{return _text; };
    Vector3f getColor(void) const{return _color; };
    float getScale(void) const{return _scale; };
    float getX(void) const{return _x; };
    float getY(void) const{return _y; };
};

#endif //GAMEENGINE_TEXTLINE_H
