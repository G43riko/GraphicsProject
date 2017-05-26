//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_GUICOMPONENT_H
#define GAMEENGINE_GUICOMPONENT_H

#include <vector>

class GuiComponent{
protected:
    std::vector<GuiComponent*> elements;
    inline void renderChildrens(const GuiRenderer& renderer){
        ITERATE_VECTOR(elements, i){
            elements[i] -> render(renderer);
        }
    }
    inline bool updateChildrens(const float delta, const Vector2f& mousePosition, bool isMouseDown){
        bool result = false;
        ITERATE_VECTOR(elements, i){
            result |= elements[i] -> update(delta, mousePosition, isMouseDown);
        }
        return result;
    }
public:
    inline void addChildren(GuiComponent* element){
        elements.push_back(element);
    }
    virtual void render(const GuiRenderer& renderer) = 0;
    virtual bool update(const float delta, const Vector2f& mousePosition, bool isMouseDown) = 0;
};

#endif //GAMEENGINE_GUICOMPONENT_H
