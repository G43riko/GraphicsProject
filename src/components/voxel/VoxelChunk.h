//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_VOXELCHUNK_H
#define GAMEENGINE_VOXELCHUNK_H

//#define MINI_CHUNK_SIZE 16

#include "MiniChunk.h"
#include "VoxelRenderer.h"
#include "VoxelPosition.h"

#define NUMBER_OF_MINICHUNKS 1

class VoxelChunk{
    MiniChunk minichunks[NUMBER_OF_MINICHUNKS];

public:
    VoxelChunk(Loader * loader){
        for(unsigned int i=0 ; i<NUMBER_OF_MINICHUNKS ; i++){
            ChunkBuilder builder({CHUNK_SIZE , CHUNK_SIZE, CHUNK_SIZE}, 1, {0, 0, 0});
            minichunks[i].setModel(loader -> loadToVao(builder.getMesh()));
        }
    }
    void render(VoxelRenderer renderer, VoxelPosition position) const{
        for(unsigned int i=0 ; i<NUMBER_OF_MINICHUNKS ; i++){
            position.setVerticalOffset(i);
            minichunks[i].render(renderer, position);
        }
    }
};

#endif //GAMEENGINE_VOXELCHUNK_H
