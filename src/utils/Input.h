//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_INPUT_H
#define GRAPHICSPROJECT_INPUT_H


#include "src/utils/math/objects/Vectors.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../rendering/WindowManager.h"

#define NUM_KEY_CODES 256
#define NUM_MOUSE_BUTTONS 5
/*
typedef struct{
    double x;
    double y;
} MousePos;
*/
class Input {
private:
//        static const int NUM_KEY_CODES = 256;
//        static const int NUM_MOUSE_BUTTONS = 5;
    static bool lastKeys[];
    static bool keys[];
    static bool lastButtons[];
    static bool buttons[];
    static Vector2f mouseScrollOffset;
    static Vector2f windowCenter;
    static Vector2f mousePos;

    inline static void onMouseScroll(GLFWwindow * window, double posX, double posY){
        mouseScrollOffset.x += (float)posX;
        mouseScrollOffset.y += (float)posY;
    }
    inline static void onKeyDown(GLFWwindow * window, int key, int scanCode, int action, int mods){
        if(action == GLFW_PRESS){
            keys[key] = true;

        }
        if(key == GLFW_KEY_KP_ADD){
            mouseScrollOffset.y += 1;
        }
        else if(key == GLFW_KEY_KP_SUBTRACT){
            mouseScrollOffset.y -= 1;
        }
        else if(action == GLFW_RELEASE){
            keys[key] = false;
        }
        //else if(action == GLFW_REPEAT);
    }
    inline static void onMouseMove(GLFWwindow * window, double posX, double posY){
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        Input::mousePos.x = (float)x;
        Input::mousePos.y = (float)y;
    }

public:
    inline static void init(int width, int height){
        glfwSetKeyCallback(WindowManager::window, onKeyDown);
        glfwSetCursorPosCallback(WindowManager::window, onMouseMove);
        glfwSetScrollCallback(WindowManager::window, onMouseScroll);
        Input::windowCenter = Vector2f(width >> 1, height >> 1);
    }
    inline static void update(void){
        for(int i = 0; i < NUM_KEY_CODES; i++){
            lastKeys[i] = isKeyDown(i);
        }

        for(int i = 0; i < NUM_MOUSE_BUTTONS; i++){
            lastButtons[i] = isButtonDown(i);
        }
    }
    inline static void setMousePos(const Vector2f pos){
        glfwSetCursorPos(WindowManager::window, pos.x, pos.y);
    }

    inline static Vector2f getMousePosition(void){return mousePos; }
    inline static Vector2f getWindowCenter(void){return windowCenter;}
    inline static Vector2f getMouseScroll(void){return mouseScrollOffset;}

    //KEYS
    inline static bool isKeyDown(int keyCode){
        return glfwGetKey(WindowManager::window, keyCode) == GLFW_PRESS;
        //return keys[keyCode];
    }

    inline static bool getKeyDown(int keyCode){
        return isKeyDown(keyCode) && !lastKeys[keyCode];
    }

    inline static bool getKeyUp(int keyCode){
        return !isKeyDown(keyCode) && lastKeys[keyCode];
    }


    //BUTTONS
    inline static bool isButtonDown(int buttonCode){
        return glfwGetMouseButton(WindowManager::window, buttonCode) == GLFW_PRESS;
        //return buttons[buttonCode];
    }
    inline static bool getMouseDown(int mouseButton){
        return isButtonDown(mouseButton) && !lastButtons[mouseButton];
    }

    inline static bool getMouseUp(int mouseButton){
        return !isButtonDown(mouseButton) && lastButtons[mouseButton];
    }

};


#endif //GRAPHICSPROJECT_INPUT_H
