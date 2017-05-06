//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_BLOCKDATABASE_H
#define GAMEENGINE_BLOCKDATABASE_H

#include <memory>
#include <vector>
#include "BlockType.h"
#include "AirType.h"
#include "GrassType.h"
#include "BlockID.h"

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ) {
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

class BlockDatabase{
private:
    std::vector<std::unique_ptr<BlockType>> blocks = std::vector<std::unique_ptr<BlockType>>((int)BlockID::NUM_BLOCK_TYPES);
    void init(void){
        blocks[(int)BlockID::Air]   = make_unique<AirType>();
        blocks[(int)BlockID::Grass] = make_unique<GrassType>();
    }

public:
    const BlockType& get(uint8_t id){
        return *blocks[id];
    }
    const BlockType& get(BlockID blockID){
        return *blocks[(int)blockID];
    }
};

#endif //GAMEENGINE_BLOCKDATABASE_H
