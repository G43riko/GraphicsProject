//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_CONTENTLOADER_H
#include "FileLoader.h"

void ContentLoader::loadTextFile(std::string fileName, std::string *content){
    std::ifstream ifs(fileName, std::ios::in);
    std::string line = "";
    if(ifs.is_open()) {
        while(!ifs.eof()) {
            std::getline(ifs, line);
            content -> append(line + "\n");
        }
        ifs.close();
        return;
    }
    Logger::error(ERROR_MISSING_FILE + fileName);
}

GLuint ContentLoader::loadTexture(std::string fileName, unsigned int width, unsigned int height){
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //std::ifstream ifs(fileName, std::ios::binary);
    std::ifstream ifs(fileName, std::ios::binary);


    if(!ifs.is_open())
        Logger::error(ERROR_MISSING_FILE + fileName);
    std::vector<char> buffer(width * height * 4);
    ifs.read(buffer.data(), buffer.size());
    ifs.close();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    return texture_id;
}
#endif