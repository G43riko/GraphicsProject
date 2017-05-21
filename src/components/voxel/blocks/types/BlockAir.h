//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_AIRTYPE_H
#define GAMEENGINE_AIRTYPE_H

#include "src/components/voxel/blocks/BlockType.h"

class BlockAir : public BlockType{
public:
    BlockAir(void) : BlockType("Air"){

    }
};


#endif //GAMEENGINE_AIRTYPE_H
