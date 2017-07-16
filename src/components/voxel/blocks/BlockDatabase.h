//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_BLOCKDATABASE_H
#define GAMEENGINE_BLOCKDATABASE_H

#include <memory>
#include <vector>
#include "src/components/voxel/blocks/types/BlockType.h"
#include "src/components/voxel/blocks/types/BlockAir.h"
#include "src/components/voxel/blocks/types/BlockGrass.h"
#include "BlockID.h"

class BlockDatabase{
    std::vector<std::unique_ptr<BlockType>> blocks = std::vector<std::unique_ptr<BlockType>>((int)BlockID::NUM_BLOCK_TYPES);
public:
    static BlockDatabase& get(){
        static BlockDatabase database;
        return database;
    }

    inline BlockDatabase(void){
        blocks[(int)BlockID::Air]   = make_unique<BlockAir>();
        blocks[(int)BlockID::Grass] = make_unique<BlockGrass>();

        get(BlockID::Grass).show();
    }
    const BlockType& get(uint8_t id) const{
        return *blocks[id];
    }
    const BlockType& get(BlockID blockID) const{
        return *blocks[(int)blockID];
    }
    const BlockType& getRandom(void) const{
        return *blocks[rand() % (int)BlockID::NUM_BLOCK_TYPES];
    }
};

#endif //GAMEENGINE_BLOCKDATABASE_H
