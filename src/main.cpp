

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "rendering/WindowManager.cpp"

#include "rendering/shader/GuiShader.cpp"
int main(){
    WindowManager::init(800, 600, "Okno");
    GuiShader * guiShader = new GuiShader();
    //BasicShader * shader = new BasicShader("GuiShader");

    while (!WindowManager::isCloseRequest()) {
        WindowManager::update();
        glfwPollEvents();
    }
    WindowManager::close();
    return 0;
}