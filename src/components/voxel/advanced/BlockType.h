//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_BLOCKTYPE_H
#define GAMEENGINE_BLOCKTYPE_H

#include <src/components/voxel/advanced/BlockData.h>
#include <string>

class BlockType{
private:
    BlockData _data;
protected:
    BlockType(const std::string fileName){

    };
public:
};

#endif //GAMEENGINE_BLOCKTYPE_H
