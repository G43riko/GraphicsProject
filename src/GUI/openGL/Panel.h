//
// Created by gabriel on 25.5.2017.
//

#ifndef GAMEENGINE_PANEL_H
#define GAMEENGINE_PANEL_H

#include "Header.h"

class Panel : public BasicElement{
    Header * header;
public:
    inline Panel(const Vector2f& position, const Vector2f& size, const bool showHeader = true) :
            BasicElement(position, size, GuiType::CHECKBOX),
            header(showHeader ? new Header(this) : nullptr){
        if(IS_NOT_NULL(header)){
            addChildren(header);
            header->setColor(Vector4f(255, 255, 255, 255));
        }
    };

};

#endif //GAMEENGINE_PANEL_H
