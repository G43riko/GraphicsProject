//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_INPUT_H
#define GRAPHICSPROJECT_INPUT_H


#include "Vectors.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../rendering/WindowManager.h"

typedef struct{
    double x;
    double y;
} MousePos;

class Input {
    private:
        static const int NUM_KEY_CODES = 256;
        static const int NUM_MOUSE_BUTTONS = 5;
        static bool lastKeys[];
        static bool keys[];
        static bool lastButtons[];
        static bool buttons[];
        static Vector2f mouseScrollOffset;
        static GLFWwindow * window;
        static Vector2f windowCenter;
        static void onKeyDown(GLFWwindow *, int, int, int, int);
        static void onMouseMove(GLFWwindow *, double, double);
        static void onMouseScroll(GLFWwindow *, double, double);
        static Vector2f mousePos;
    public:
        static Vector2f getWindowCenter(void);
        static Vector2f getMousePosition(void);
        static void init(GLFWwindow*, int, int);
        static void update(void);
        static void setMousePos(Vector2f);
        static Vector2f getMouseScroll(void){
            return mouseScrollOffset;
        }
        //KEYS
        static bool isKeyDown(int);
        static bool getKeyDown(int);
        static bool getKeyUp(int);

        //BUTTONS
        static bool isButtonDown(int);
        static bool getMouseDown(int);
        static bool getMouseUp(int);
};


#endif //GRAPHICSPROJECT_INPUT_H
