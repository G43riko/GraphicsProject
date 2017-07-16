//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_MINICHUNK_H
#define GAMEENGINE_MINICHUNK_H

#include "src/components/voxel/VoxelPosition.h"
#include "src/components/voxel/blocks/VoxelBlock.h"
#include "src/components/voxel/VoxelRenderer.h"
#include "ChunkBuilder.h"


//#define GET_MINICHUNK_LOCATION(x, y, z) (x * MINI_CHUNK_AREA + y * MINI_CHUNK_SIZE + z)
//#define IS_REAL_POSITION(x, y, z) (x < MINI_CHUNK_SIZE && y < MINI_CHUNK_SIZE && z < MINI_CHUNK_SIZE)

//const int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
//const int CHUNK_VOLUME = CHUNK_AREA * CHUNK_SIZE;

class MiniChunk{
    PointerRawModel model;
    VoxelBlock * blocks[CHUNK_VOLUME];
//    const int _height;
    inline static uint getLocation(uint x, uint y, uint z){ return  x * CHUNK_AREA + y * CHUNK_SIZE + z; }
    inline static bool isRealPosition(uint x, uint y, uint z){ return x < CHUNK_SIZE && y < CHUNK_SIZE && z < CHUNK_SIZE; }
public:
    //MiniChunk(UInt height) : _height(height){}
    MiniChunk(PointerRawModel model = nullptr) : model(model){}
    void setModel(PointerRawModel model) {this ->model = model;}

    inline VoxelBlock * getBlock(uint x, uint y, uint z) const{
        return isRealPosition(x, y, z) ? blocks[getLocation(x, y, z)] : nullptr;
    }

    inline void setBlock(uint x, uint y, uint z, VoxelBlock * block){
        if(isRealPosition(x, y, z)){
            blocks[getLocation(x, y, z)] = block;
        }
    }
};

#endif //GAMEENGINE_MINICHUNK_H
