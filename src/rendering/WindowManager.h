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
        static int init(const int, const int, std::string, bool = false);
        static void close(void);
        static bool isCloseRequest(void);
        static void update(void);
        static int width;
        static int height;
        static float getRation(void);
        static GLFWwindow* window;
    private:
        static const int contentAttributesMinorVersion = 3;
        static const int contentAttributesMajorVersion = 3;
        static const int samples = 4;

        WindowManager(void);
};

#endif //GRAPHICSPROJECT_WINDOWMANAGER_H
