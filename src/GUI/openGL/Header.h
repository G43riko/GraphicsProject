//
// Created by gabriel on 25.5.2017.
//

#ifndef GAMEENGINE_HEADER_H
#define GAMEENGINE_HEADER_H

#include "BasicElement.h"

#define DEFAULT_GUI_HEADER_HEIGHT 0.03f
/*
 * - krížik na zavretie
 * - čiara na na minimalizovanie
 */
class Header : public BasicElement{
    BasicElement * _parent;
    float _height;
public:
    inline Header(BasicElement * parent, const float height = DEFAULT_GUI_HEADER_HEIGHT) :
            BasicElement(parent -> getRelativePosition(), parent -> getRelativeSize()),
            _parent(parent),
            _height(height){
    }

    virtual inline void render(const GuiRenderer& renderer) override{
        Vector2f size = _parent -> getRelativeSize();
        Vector2f position = _parent -> getRelativePosition();
        position.y += size.y - _height;
        size.y = _height;
        renderer.renderRect(position, size, getBgTextureId());

        renderChildrens(renderer);
    }
};
#endif //GAMEENGINE_HEADER_H
