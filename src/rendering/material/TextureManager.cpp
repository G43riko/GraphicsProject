//
// Created by gabriel on 22.1.2017.
//

#include <src/rendering/material/TextureManager.h>

std::map<std::string, PointerTexture2D> TextureManager::loadedTextures2D;
std::map<std::string, PointerCubeTexture> TextureManager::loadedCubeTextures;
std::map<std::string, PointerParticleTexture> TextureManager::loadedParticleTextures;