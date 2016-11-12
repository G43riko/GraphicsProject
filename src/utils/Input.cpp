//
// Created by gabriel on 25.9.2016.
//

#include "Input.h"

GLFWwindow * Input::window = nullptr;
Vector2f Input::windowCenter;
Vector2f Input::mousePos = Vector2f();
Vector2f Input::getMousePosition(void){
    return mousePos;
};
Vector2f Input::getWindowCenter(void){
    return windowCenter;
}
bool Input::lastKeys[NUM_KEY_CODES] = {false};
bool Input::keys[NUM_KEY_CODES] = {false};
bool Input::lastButtons[NUM_MOUSE_BUTTONS] = {false};
bool Input::buttons[NUM_MOUSE_BUTTONS] = {false};

void Input::init(GLFWwindow* window, int width, int height){
    Input::window = window;
    glfwSetKeyCallback(window, Input::onKeyDown);
    glfwSetCursorPosCallback(window, Input::onMouseMove);
    Input::windowCenter = Vector2f(width >> 1, height >> 1);
}

void Input::setMousePos(Vector2f  pos){
    glfwSetCursorPos(Input::window, pos.x, pos.y);
}

void Input::onKeyDown(GLFWwindow * window, int key, int scanCode, int action, int mods){
    if(action == GLFW_PRESS){
        keys[key] = true;
    }
    else if(action == GLFW_RELEASE){
        keys[key] = false;
    }
    //else if(action == GLFW_REPEAT);
}
void Input::onMouseMove(GLFWwindow * window, double posX, double posY){
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    Input::mousePos.x = (float)x;
    Input::mousePos.y = (float)y;
}

void Input::update(void){
    for(int i = 0; i < NUM_KEY_CODES; i++)
        lastKeys[i] = isKeyDown(i);

    for(int i = 0; i < NUM_MOUSE_BUTTONS; i++)
        lastButtons[i] = isButtonDown(i);
}
void Input::setMousePos(Vector2f);
//KEYS

bool Input::isKeyDown(int keyCode){
    return glfwGetKey(Input::window, keyCode) == GLFW_PRESS;
    //return keys[keyCode];
}

//KEYBOARD

bool Input::getKeyDown(int keyCode){
    return isKeyDown(keyCode) && !lastKeys[keyCode];
}

bool Input::getKeyUp(int keyCode){
    return !isKeyDown(keyCode) && lastKeys[keyCode];
}

//MOUSE

bool Input::isButtonDown(int buttonCode){
    return glfwGetMouseButton(Input::window, buttonCode) == GLFW_PRESS;
    //return buttons[buttonCode];
}
bool Input::getMouseDown(int mouseButton){
    return isButtonDown(mouseButton) && !lastButtons[mouseButton];
}

bool Input::getMouseUp(int mouseButton){
    return !isButtonDown(mouseButton) && lastButtons[mouseButton];
}
