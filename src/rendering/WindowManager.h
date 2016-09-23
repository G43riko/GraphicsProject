//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_WINDOWMANAGER_H
#define GRAPHICSPROJECT_WINDOWMANAGER_H

#include "../utils/Const.h"
#include "../utils/Logger.cpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowManager {
    public:
        static int init(int, int, std::string);
        static void close();
        static bool isCloseRequest();
        static void update();
    private:
        static const int contentAttributesMinorVersion = 3;
        static const int contentAttributesMajorVersion = 3;
        static const int samples = 4;

        static GLFWwindow* window;
        WindowManager(void);
};

#endif //GRAPHICSPROJECT_WINDOWMANAGER_H
