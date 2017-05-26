//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_FLARETEXTURE_H
#define GAMEENGINE_FLARETEXTURE_H

#include <src/components/gui/GuiTexture.h>

class FlareTexture : public GuiTexture{
    float _blend;
public:
    inline FlareTexture(GLuint id,
                        const Vector2f & position = Vector2f(0.75f, 0.75f),
                        const Vector2f & scale = Vector2f(0.25f, 0.25f),
                        float blend = 1) :
            GuiTexture(id, position, scale),
            _blend(blend){
    }

};

#endif //GAMEENGINE_FLARETEXTURE_H
