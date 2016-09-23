

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "rendering/WindowManager.cpp"


int main(){
    WindowManager::init(800, 600, "Okno");

    // Main execution loop
    while (!WindowManager::isCloseRequest()) {
        // Display result
        WindowManager::update();
        glfwPollEvents();
    }
    WindowManager::close();
    return 0;
}