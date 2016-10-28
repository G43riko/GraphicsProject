//
// Created by gabriel on 22.9.2016.
//

#include "WindowManager.h"

WindowManager::WindowManager(void) {}
GLFWwindow* WindowManager::window;
int WindowManager::width;
int WindowManager::height;

bool WindowManager::isCloseRequest(void){
    return glfwWindowShouldClose(WindowManager::window);
}
void WindowManager::update(void){
    glfwSwapBuffers(WindowManager::window);
    glfwPollEvents();
}

void WindowManager::close(void) {
    glfwTerminate();
}


int WindowManager::init(int width, int height, std::string title, bool fullscreen){
    //inicializuje openGL
    if (!glfwInit()) {
        Logger::error(ERROR_INITIAL_GLFW);
        return EXIT_FAILURE;
    }
    //nastaví openGL
    glfwWindowHint(GLFW_SAMPLES, WindowManager::samples);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WindowManager::contentAttributesMinorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WindowManager::contentAttributesMajorVersion);
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
        Logger::error(ERROR_INITIAL_GLEW);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}