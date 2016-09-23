//
// Created by gabriel on 22.9.2016.
//

#include "WindowManager.h"

WindowManager::WindowManager(void) {}
GLFWwindow* WindowManager::window;

bool WindowManager::isCloseRequest(){
    return glfwWindowShouldClose(WindowManager::window);
}
void WindowManager::update(){
    glClearColor(1, 0, 1, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(WindowManager::window);
}

void WindowManager::close() {
    glfwTerminate();
}

int WindowManager::init(int width, int height, std::string title){
    //inicializuje openGL
    if (!glfwInit()) {
        Logger::error(ERROR_INITIAL_GLFW);
    }
    //nastaví openGL
    glfwWindowHint(GLFW_SAMPLES, WindowManager::samples);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WindowManager::contentAttributesMinorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WindowManager::contentAttributesMajorVersion);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Vytvorí okno
    WindowManager::window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
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