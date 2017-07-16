//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_BLOCKDATA_H
#define GAMEENGINE_BLOCKDATA_H

#include <string>
#include <fstream>
#include <src/utils/math/objects/Vectors.h>

#include "BlockID.h"


class BlockData{
    BlockID _blockID;
    std::string _name;
    bool _isOpaque;
    Vector2f _texturesTop;
    Vector2f _texturesSide;
    Vector2f _texturesBottom;
public:
    inline BlockData(const std::string& fileName){
        std::ifstream inFile;
        inFile.open("/res/voxel_old/blocks/" + fileName + ".block");

        std::string title;

        while(std::getline(inFile, title)){
            if(title == ""){
                continue;
            }
            else if(title == "Name"){
                inFile >> _name;
            }
            else if(title == "ID"){
                int id;
                inFile >> id;
                _blockID = static_cast<BlockID>(id);
            }
            else if(title == "Opaque"){
                inFile >> _isOpaque;
            }
            else if(title == "TextureTop"){
                inFile >> _texturesTop.x >> _texturesTop.y;
            }
            else if(title == "TextureSide"){
                inFile >> _texturesSide.x >> _texturesSide.y;
            }
            else if(title == "TextureBottom"){
                inFile >> _texturesBottom.x >> _texturesBottom.y;
            }
        }
    };

    inline void show(void) const{
        std::cout << "Name: " << _name << ", TextureTop: " << _texturesTop << ", TextureSide: " << _texturesSide;
    }
};

#endif //GAMEENGINE_BLOCKDATA_H
