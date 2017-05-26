//
// Created by gabriel on 25.5.2017.
//

#ifndef GAMEENGINE_CHECKBOX_H
#define GAMEENGINE_CHECKBOX_H

#include <src/rendering/material/TextureManager.h>
#include "BasicElement.h"

class CheckBox : public BasicElement{
    bool * _property = nullptr;
    bool _checked = false;
    PointerTexture2D trueTexture = TextureManager::instance.createTexture2D(Vector3f(0.0f, 255.0f, 0.0f));
    PointerTexture2D falseTexture = TextureManager::instance.createTexture2D(Vector3f(255.0f, 255.0f, 0.0f));
public:
    inline CheckBox(const Vector2f& position, const Vector2f& size, const bool checked = false) :
            BasicElement(position, size, GuiType::CHECKBOX),
            _checked(checked){
        setHoverColor(Vector4f(0, 0, 255, 255));
    }
    virtual inline void onClick(const Vector2f& mousePos) override{
        _checked = !_checked;
        if(IS_NOT_NULL(_property)){
            *_property = _checked;
        }
    }
    virtual inline void render(GuiRenderer& renderer){
        const uint texture = _checked ? trueTexture -> getTextureID() : falseTexture -> getTextureID();
        renderer.renderRect(getRelativePosition(), getRelativeSize(), texture);

        renderChildrens(renderer);
    }

    virtual inline void show(const std::string& key = "", const bool breakLine = true) const override{
        BasicElement::show(key, false);
        printf(", checked: %s%c", _checked ? "true" : "false", breakLine ? '\n' : ' ');
    }
};

#endif //GAMEENGINE_CHECKBOX_H
