//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_CONTENTLOADER_H
#define GRAPHICSPROJECT_CONTENTLOADER_H

#include <string>
#include "Const.h"
#include "utils.cpp"
#include "Logger.cpp"
#include <fstream>
#include <vector>
#include <GL/glew.h>

class ContentLoader {
    public:
        static void loadTextFile(std::string, std::string *);
        static GLuint loadTexture(std::string, unsigned int, unsigned int);
};


#endif //GRAPHICSPROJECT_CONTENTLOADER_H
