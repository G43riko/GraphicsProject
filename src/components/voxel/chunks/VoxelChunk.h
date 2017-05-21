//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_VOXELCHUNK_H
#define GAMEENGINE_VOXELCHUNK_H

//#define MINI_CHUNK_SIZE 16

#include "MiniChunk.h"
#include "src/components/voxel/VoxelRenderer.h"
#include "src/components/voxel/VoxelPosition.h"


class VoxelChunk{
    MiniChunk minichunks[NUMBER_OF_MINICHUNKS];
    PointerRawModel model;
public:
    inline VoxelChunk(Vector2f pos, Loader * loader){
        Vector3f position = Vector3f(pos.x * CHUNK_SIZE, 0.0f, pos.y * CHUNK_SIZE);
        ////toto generuje každý miniChunk samostatne
//        for(uint i=0 ; i<NUMBER_OF_MINICHUNKS ; i++){
//            ChunkBuilder builder({CHUNK_SIZE , CHUNK_SIZE, CHUNK_SIZE}, BLOCK_SIZE);
//            builder.generate(position);
//            position.y += CHUNK_SIZE;
//            minichunks[i].setModel(loader -> loadToVao(builder.getMesh()));
//        }


        ////toto generuje dokopy celý chunk
        ChunkBuilder builder({CHUNK_SIZE , CHUNK_SIZE, CHUNK_SIZE}, BLOCK_SIZE);
        LOOP(NUMBER_OF_MINICHUNKS, i){
            builder.generate(position);
            position.y += CHUNK_SIZE;
        }
        model = loader -> loadToVao(builder.getMesh());

    }
    inline void render(VoxelRenderer renderer, VoxelPosition position) const{
        ////toto renderuje každy minichunk samostatne
//        for(uint i=0 ; i<NUMBER_OF_MINICHUNKS ; i++){
//            minichunks[i].render(renderer, position);
//        }

        ////toto renderuje chunky samostatne
        renderer.render({0, (int)position.getVerticalOffset() * 16, 0}, model);
    }
};

#endif //GAMEENGINE_VOXELCHUNK_H
