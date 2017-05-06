//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_BLOCKDATA_H
#define GAMEENGINE_BLOCKDATA_H

#include <string>
#include <fstream>

#include "BlockID.h"


class BlockData{
private:
    BlockID _blockID;
    std::string _name;
    bool _isOpaque;
public:

    BlockData(const std::string& fileName){
        std::ifstream inFile;
        inFile.open("/res/voxel/blocks/" + fileName + ".block");

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
        }
    };
};

#endif //GAMEENGINE_BLOCKDATA_H
