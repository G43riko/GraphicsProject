//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_MINICHUNK_H
#define GAMEENGINE_MINICHUNK_H

#include "VoxelPosition.h"
#include "VoxelBlock.h"
#include "VoxelRenderer.h"
#include "../voxel_old/ChunkBuilder.h"

typedef unsigned int UInt;

//#define GET_MINICHUNK_LOCATION(x, y, z) (x * MINI_CHUNK_AREA + y * MINI_CHUNK_SIZE + z)
//#define IS_REAL_POSITION(x, y, z) (x < MINI_CHUNK_SIZE && y < MINI_CHUNK_SIZE && z < MINI_CHUNK_SIZE)

//const int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
//const int CHUNK_VOLUME = CHUNK_AREA * CHUNK_SIZE;

class MiniChunk{
    PointerRawModel model;
    VoxelBlock * blocks[CHUNK_VOLUME];
//    const int _height;
    inline static UInt getLocation(UInt x, UInt y, UInt z){ return  x * CHUNK_AREA + y * CHUNK_SIZE + z; }
    inline static bool isRealPosition(UInt x, UInt y, UInt z){ return x < CHUNK_SIZE && y < CHUNK_SIZE && z < CHUNK_SIZE; }
public:
    //MiniChunk(UInt height) : _height(height){}
    MiniChunk(PointerRawModel model = nullptr) : model(model){}
    void setModel(PointerRawModel model) {this ->model = model;}
    inline VoxelBlock * getBlock(UInt x, UInt y, UInt z) const{
        return isRealPosition(x, y, z) ? blocks[getLocation(x, y, z)] : nullptr;
    }
    inline void setBlock(UInt x, UInt y, UInt z, VoxelBlock * block){
        if(isRealPosition(x, y, z)){
            blocks[getLocation(x, y, z)] = block;
        }
    }

    void render(VoxelRenderer renderer, VoxelPosition position) const{
        renderer.render({0, (int)position.getVerticalOffset() * 16, 0}, model);
    }
};

#endif //GAMEENGINE_MINICHUNK_H
