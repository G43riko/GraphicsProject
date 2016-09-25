//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_INPUT_H
#define GRAPHICSPROJECT_INPUT_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
typedef bool * boolArray;

class Input {
    private:
        static const int NUM_KEY_CODES = 256;
        static const int NUM_MOUSE_BUTTONS = 5;
        static bool lastKeys[];
        static bool keys[];
        static bool lastButtons[];
        static bool buttons[];
        static GLFWwindow * window;

        static void onKeyDown(GLFWwindow * window, int key, int scanCode, int action, int mods){

            if(action == GLFW_PRESS){
                keys[key] = true;
            }
            else if(action == GLFW_RELEASE){
                keys[key] = false;
            }
            //else if(action == GLFW_REPEAT);
        }
    public:
        static void init(GLFWwindow * window){
            Input::window = window;
            glfwSetKeyCallback(window, Input::onKeyDown);
        }
        static void update(void){
            for(int i = 0; i < NUM_KEY_CODES; i++)
                lastKeys[i] = isKeyDown(i);

            for(int i = 0; i < NUM_MOUSE_BUTTONS; i++)
                lastButtons[i] = isButtonDown(i);
        }

        //KEYS

        static bool isKeyDown(int keyCode){
            return glfwGetKey(window, keyCode) == GLFW_PRESS;
            //return keys[keyCode];
        }

        static bool getKeyDown(int keyCode){
            return isKeyDown(keyCode) && !lastKeys[keyCode];
        }

        static bool getKeyUp(int keyCode){
            return !isKeyDown(keyCode) && lastKeys[keyCode];
        }

        //BUTTONS

        static bool isButtonDown(int buttonCode){
            return glfwGetMouseButton(window, buttonCode) == GLFW_PRESS;
            //return buttons[buttonCode];
        }
        static bool getMouseDown(int mouseButton){
            return isButtonDown(mouseButton) && !lastButtons[mouseButton];
        }

        static bool getMouseUp(int mouseButton){
            return !isButtonDown(mouseButton) && lastButtons[mouseButton];
        }
        static int KEY_W, KEY_A, KEY_S, KEY_D, KEY_Q, KEY_E, KEY_LSHIFT, KEY_SPACE;
};


#endif //GRAPHICSPROJECT_INPUT_H
