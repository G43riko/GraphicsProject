//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_CONTENTLOADER_H
#include "ContentLoader.h"

std::string ContentLoader::loadFileContent(std::string fileName){
    std::ifstream ifs(fileName);
    if(ifs.good()){
        std::string content( (std::istreambuf_iterator<char>(ifs)),  (std::istreambuf_iterator<char>()));
        return content;
    }
    Logger::error(ERROR_MISSING_FILE + fileName);
    return "";
}
#endif