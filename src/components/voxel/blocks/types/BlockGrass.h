//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_GRASSTYPE_H
#define GAMEENGINE_GRASSTYPE_H

#include "src/components/voxel/blocks/BlockType.h"

class BlockGrass : public BlockType{
    public:
        BlockGrass(void) : BlockType("Grass"){

        }
};

#endif //GAMEENGINE_GRASSTYPE_H
