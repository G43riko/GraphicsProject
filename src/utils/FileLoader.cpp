//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_CONTENTLOADER_H

#include "FileLoader.h"

std::vector<std::string> ContentLoader::TITLES = {"Right", "Left", "Top", "Bottom", "Back", "Front"};


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

PointerTexture2D ContentLoader::loadTexture(std::string fileName, unsigned int width, unsigned int height){
    //std::ifstream ifs(fileName, std::ios::binary);
    std::ifstream ifs(fileName, std::ios::binary);


    if(!ifs.is_open())
        Logger::error(ERROR_MISSING_FILE + fileName);
    std::vector<unsigned char> buffer(width * height * 4);
    ifs.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    ifs.close();

    return initTexture2D(fileName, buffer, width, height);
}
#endif