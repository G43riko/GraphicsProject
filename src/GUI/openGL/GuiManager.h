//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_GUIMANAGER_H
#define GAMEENGINE_GUIMANAGER_H

#include <vector>
#include "BasicElement.h"
#include "CheckBox.h"
#include "Panel.h"
#include <src/rendering/shader/GuiShader.h>

class GuiManager{
    std::vector<BasicElement*> elements;
    GuiRenderer renderer;
    Vector2f lastMousePosition;
public:
    inline GuiManager(BasicShader * shader, const PointerRawModel model) :
            renderer(shader, model){
        BasicElement * element = new Panel({200.0f, 200.0f},
                                           {256.0f, 256.0f}, false);
        element -> setColor({255, 0, 255, 255}).setHoverColor({0, 255, 255, 255}).setActiveColor({255, 0, 0, 255});
        element -> show("basicElement");
        elements.push_back(element);
//        CheckBox * checkBox = new CheckBox({216.0f, 216.0f},
//                                           {128.0f, 128.0f});
//        checkBox -> show("checkbox");
//        element -> addChildren(checkBox);
    };

    inline void update(float delta){
        Vector2f mousePos = Input::getMousePosition();
        mousePos.y = (float)WindowManager::height - mousePos.y;

        if(NEZ(mousePos.x - lastMousePosition.x) ||
           NEZ(mousePos.y - lastMousePosition.y) ||
           Input::getMouseDown(MOUSE_LEFT_BUTTON) ||
           Input::getMouseUp(MOUSE_LEFT_BUTTON)){
            bool isInElement = false;
            ITERATE_VECTOR(elements, i){
                isInElement |= elements[i] -> update(delta, mousePos, Input::isButtonDown(MOUSE_LEFT_BUTTON));
            }

            if(!isInElement){
                WindowManager::setCursor(WindowManager::CURSOR_ARROW);
            }
        }

        lastMousePosition = mousePos;
    }

    inline void render(void){
        Vector2f mousePosition = Input::getMousePosition();
        mousePosition.y = (float)WindowManager::height - mousePosition.y;
        ITERATE_VECTOR(elements, i){
            elements[i] -> render(renderer);
        }
    }
    inline bool isEmpty(void) const{return elements.empty();}
};

#endif //GAMEENGINE_GUIMANAGER_H
