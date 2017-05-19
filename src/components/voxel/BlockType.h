//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_BLOCKTYPE_H
#define GAMEENGINE_BLOCKTYPE_H

#include <src/components/voxel/BlockData.h>
#include <string>

class BlockType{
private:
    BlockData _data;
protected:
    virtual BlockType(const std::string fileName) : _data(fileName){};
public:
    inline void show(void) const{
        _data.show();
    }
};

#endif //GAMEENGINE_BLOCKTYPE_H
