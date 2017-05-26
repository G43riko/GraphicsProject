//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_BASICELEMENT_H
#define GAMEENGINE_BASICELEMENT_H

#include <src/utils/math/objects/Vectors.h>
#include <src/utils/math/collisions/Collisions2D.h>
#include "GuiRenderer.h"
#include "GuiComponent.h"

enum GuiType{
    PLAIN,
    BUTTON,
    CHECKBOX
};

class BasicElement : public GuiComponent{
    struct ColorData{
        PointerTexture2D texture;
        Vector4f color;
        inline ColorData(const Vector4f& col = Vector4f(0, 0, 0, 255)){
            setColor(color);
        }
        inline void setColor(const Vector4f& col){
            TextureManager::instance.removeTexture(col.getXYZ());
            color = col;
            texture = TextureManager::instance.createTexture2D(col.getXYZ());
        }
    };
    GuiType _type;
    bool _changeCursor = true;
    int _hoverCursor = GLFW_HAND_CURSOR;
    Vector2f _relativePosition;
    Vector2f _relativeSize;
    Vector2f _position;
    Vector2f _size;
protected:
    bool hover = false;
    bool active = false;
    ColorData bgColor = ColorData();
    ColorData hoverColor = ColorData();
    ColorData activeColor = ColorData();

    inline uint getBgTextureId(void) const{
        uint color = bgColor.texture -> getTextureID();
        if(hover){
            color = active ? activeColor.texture -> getTextureID() : hoverColor.texture -> getTextureID();
        }
        return color;
    }
public:
    inline static Vector2f toAbsolutePosition(const Vector2f& position){
        return (position + 1) * Vector2f(WindowManager::width, WindowManager::height) >> 1 ;
    }
    inline static Vector2f toAbsoluteSize(const Vector2f& size){
        return size * Vector2f(WindowManager::width, WindowManager::height);
    }
    inline BasicElement(const Vector2f& position,
                        const Vector2f& size,
                        GuiType type = GuiType::PLAIN) : _type(type){
        setPosition(position);
        setSize(size);
    };

    virtual inline void onClick(const Vector2f& mousePos){}

    virtual inline void show(const std::string& key = "", const bool breakLine = true) const{
        printf("%s: position: [%f, %f], size: [%f, %f]%c",
               key.c_str(),
               _position.x,
               _position.y,
               _size.x,
               _size.y,
               breakLine ? '\n' : ' ');
    }
    virtual inline bool update(const float delta, const Vector2f& mousePosition, const bool isMouseDown) override{
        hover = Collisions2D::pointRect(mousePosition, getMinPos(), _size);
        if(hover){
            if(active && !isMouseDown){
                onClick(mousePosition);
            }
            active = isMouseDown;
            if(_changeCursor){
                WindowManager::setCursor(glfwCreateStandardCursor(_hoverCursor));
            }
        }
        return updateChildrens(delta, mousePosition, isMouseDown) && _changeCursor && hover;
    }
    virtual inline void render(const GuiRenderer& renderer) override{
        renderer.renderRect(_relativePosition, _relativeSize, getBgTextureId());

        renderChildrens(renderer);
    }

    //SETTERS


    inline BasicElement& setPosition(const Vector2f& position){
        _relativePosition = (position / Vector2f(WindowManager::width, WindowManager::height) - 0.5f) * 2;
        _position = position;
        return *this;
    }
    inline BasicElement& setSize(const Vector2f& size){
        _relativeSize = (size / Vector2f(WindowManager::width, WindowManager::height));
        _size = size;
        return *this;
    }
    inline BasicElement& setColor(const Vector4f& color){
        bgColor.setColor(color);
        return *this;
    }
    inline BasicElement& setHoverColor(const Vector4f& color){
        hoverColor.setColor(color);
        return *this;
    }
    inline BasicElement& setActiveColor(const Vector4f& color){
        activeColor.setColor(color);
        return *this;
    }
    inline BasicElement& setChangeCursor(const bool value){
        _changeCursor = value;
        return *this;
    }
    inline BasicElement& setHoverCursor(const int value){
        _hoverCursor = value;
        return *this;
    }

    //GETTERS

    inline const Vector2f& getRelativePosition(void) const{ return _relativePosition; }
    inline Vector2f getMinPos(void) const{return Vector2f(getLeft(), getBottom());}
    inline const Vector2f& getRelativeSize(void) const{ return _relativeSize;}
    inline Vector2f getMaxPos(void) const{return getMinPos() + _size;}

    inline float getRight(void) const{ return _position.x + (float)(_size.getXi() >> 1); }
    inline float getTop(void) const{ return _position.y + (float)(_size.getYi() >> 1); }
    inline float getBottom(void) const{ return _position.y - (float)(_size.getYi() >> 1); }
    inline float getLeft(void) const{ return _position.x - (float)(_size.getXi() >> 1); }


    inline float getRelativeBottom(void) const{ return _relativePosition.y - _relativeSize.y / 2.0f; }
    inline float getRelativeRight(void) const{ return _relativePosition.x + _relativeSize.x / 2.0f; }
    inline float getRelativeLeft(void) const{ return _relativePosition.x - _relativeSize.x / 2.0f; }
    inline float getRelativeTop(void) const{ return _relativePosition.y + _relativeSize.y / 2.0f; }

};

#endif //GAMEENGINE_BASICELEMENT_H
