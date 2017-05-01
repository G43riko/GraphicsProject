//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_WINDOWMANAGER_H
#define GRAPHICSPROJECT_WINDOWMANAGER_H

#include "../utils/Const.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <src/utils/utils.h>

#define CONTENT_ATTRIBUTES_MINOR_VERSION 3
#define CONTENT_ATTRIBUTES_MAJOR_VERSION 3
#define SAMPLES 4

class WindowManager {
public:
    static GLFWwindow * window;

    static inline void update(void){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    static inline void close(void) {
        glfwTerminate();
        glfwDestroyWindow(window);
    }
    static int width;
    static int height;
    static inline float getRation(void){
        return (float) width / (float) height;
    }

    static inline bool isCloseRequest(void){
        return glfwWindowShouldClose(WindowManager::window) == GL_TRUE;
    }
    static inline int init(int width, int height, std::string title, bool fullscreen){
        //inicializuje openGL
        if (!glfwInit()) {
            ERROR(ERROR_INITIAL_GLFW);
            return EXIT_FAILURE;
        }
        //nastaví openGL
        glfwWindowHint(GLFW_SAMPLES, SAMPLES);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTENT_ATTRIBUTES_MINOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTENT_ATTRIBUTES_MAJOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //Vytvorí okno

        GLFWmonitor * monitor = nullptr;
        if(fullscreen){
            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode * mode = glfwGetVideoMode(monitor);

            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            width = mode -> width;
            height = mode -> height;
        }
        WindowManager::width = width;
        WindowManager::height = height;

        WindowManager::window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
        if (!WindowManager::window) {
            //Logger::error(ERROR_OPEN_GLFW_WINDOW);
            glfwTerminate();
            return EXIT_FAILURE;
        }
        //nastaví aktualne okno
        glfwMakeContextCurrent(WindowManager::window);

        //inicializujeme glew
        glewExperimental = GL_TRUE;
        glewInit();
        if (!glewIsSupported("GL_VERSION_3_3")) {
            ERROR(ERROR_INITIAL_GLEW);
            glfwTerminate();
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
private:
    WindowManager(void){};
};



#endif //GRAPHICSPROJECT_WINDOWMANAGER_H
