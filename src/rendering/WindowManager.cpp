//
// Created by gabriel on 22.9.2016.
//

#include "WindowManager.h"

GLFWwindow* WindowManager::window;
int WindowManager::width;
int WindowManager::height;


GLFWcursor * WindowManager::CURSOR_HRESIZE = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
GLFWcursor * WindowManager::CURSOR_VRESIZE = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
GLFWcursor * WindowManager::CURSOR_POINTER = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
GLFWcursor * WindowManager::CURSOR_ARROW = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);


