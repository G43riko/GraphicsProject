//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_BLOCKTYPE_H
#define GAMEENGINE_BLOCKTYPE_H

#include <src/components/voxel/blocks/BlockData.h>
#include <string>

class BlockType{
    BlockData _data;
protected:
    BlockType(const std::string& fileName) : _data(fileName){};
public:
    inline const BlockData& getData(void) const{
        return _data;
    }
    inline void show(void) const{
        _data.show();
    }
};

#endif //GAMEENGINE_BLOCKTYPE_H
