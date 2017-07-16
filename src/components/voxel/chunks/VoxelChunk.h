//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_VOXELCHUNK_H
#define GAMEENGINE_VOXELCHUNK_H

#include "MiniChunk.h"
#include "src/components/voxel/VoxelRenderer.h"
#include "src/components/voxel/VoxelPosition.h"


class VoxelChunk{
    MiniChunk minichunks[NUMBER_OF_MINICHUNKS];
    PointerRawModel model;
public:
    inline VoxelChunk(Vector2f pos, Loader * loader){
        Vector3f position = Vector3f(pos.x * CHUNK_SIZE, 0.0f, pos.y * CHUNK_SIZE);

        ////toto generuje dokopy celý chunk
        ChunkBuilder builder({CHUNK_SIZE , CHUNK_SIZE, CHUNK_SIZE}, BLOCK_SIZE);

        LOOP(NUMBER_OF_MINICHUNKS, i){
            builder.generate(position);
            position.y += CHUNK_SIZE;
        }

        model = loader -> loadToVao(builder.getMesh());

    }
    inline void render(const VoxelRenderer& renderer, VoxelPosition position) const{
        ////toto renderuje chunky samostatne
        renderer.render(*model);
    }
};

#endif //GAMEENGINE_VOXELCHUNK_H
