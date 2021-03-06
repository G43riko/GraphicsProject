//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_WOLDCONST_H
#define GAMEENGINE_WOLDCONST_H

#define WOXEL_TEXTURE_NUM_X 8
#define WOXEL_TEXTURE_NUM_Y 8

#define BLOCK_SIZE 1

#define NUMBER_OF_MINICHUNKS 1
#define CHUNK_HEIGHT 256

#define WORLD_SIZE 128

#define VISIBLE_ALL 127
#define VISIBLE_NONE 0

namespace {
    constexpr static int    CHUNK_SIZE      = 32,
                            REAL_CHUNK_SIZE = CHUNK_SIZE * BLOCK_SIZE * 2,
                            WOLD_MAX        = WORLD_SIZE * CHUNK_SIZE,
                            CHUNK_AREA      = CHUNK_SIZE * CHUNK_SIZE,
                            CHUNK_VOLUME    = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

    constexpr static int    MAX_LIGHT       = 10;
}



#endif //GAMEENGINE_WOLDCONST_H
