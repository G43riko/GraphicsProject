//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_RESOURCESMANAGER_H
#define GAMEENGINE_RESOURCESMANAGER_H

#include <src/rendering/material/TextureManager.h>

class ResourcesManager {

    //TEXTURES
    static inline PointerTexture2D createTexture2D(std::string fileName){
        return TextureManager::createTexture2D(fileName);
    };
    static inline PointerTexture2D createTexture2D(Vector3f color){
        return TextureManager::createTexture2D(color);
    };
    static inline PointerCubeTexture createCubeTexture(std::string fileName){
        return TextureManager::createCubeTexture(fileName);
    };
    static inline PointerParticleTexture createParticleTexture(std::string fileName, int rows, int columns){
        return TextureManager::createParticleTexture(fileName, rows, columns);
    };
};


#endif //GAMEENGINE_RESOURCESMANAGER_H
