//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_WOLDCONST_H
#define GAMEENGINE_WOLDCONST_H

#define BLOCK_SIZE_X 1
#define BLOCK_SIZE_Y 1
#define BLOCK_SIZE_Z 1

#define MAX_BLOCKS_X 16
#define MAX_BLOCKS_Y 32
#define MAX_BLOCKS_Z 16

#define MAX_CHUNKS_X 128
#define MAX_CHUNKS_Y 4
#define MAX_CHUNKS_Z 128

#define VISIBLE_ALL 127
#define VISIBLE_NONE 0

/*
#define CHUNK_SIZE_X (MAX_BLOCKS_X * BLOCK_SIZE_X * 2)
#define CHUNK_SIZE_Y (MAX_BLOCKS_Y * BLOCK_SIZE_Y * 2)
#define CHUNK_SIZE_Z (MAX_BLOCKS_Z * BLOCK_SIZE_Z * 2)

#define WOLD_MAX_X (MAX_CHUNKS_X * MAX_BLOCKS_X)
#define WOLD_MAX_Y (MAX_CHUNKS_Y * MAX_BLOCKS_Y)
#define WOLD_MAX_Z (MAX_CHUNKS_Z * MAX_BLOCKS_Z)
*/

namespace{
    constexpr static int    CHUNK_SIZE_X    = MAX_BLOCKS_X * BLOCK_SIZE_X * 2,
                            CHUNK_SIZE_Y    = MAX_BLOCKS_Y * BLOCK_SIZE_Y * 2,
                            CHUNK_SIZE_Z    = MAX_BLOCKS_Z * BLOCK_SIZE_Z * 2,
                            WOLD_MAX_X      = MAX_CHUNKS_X * MAX_BLOCKS_X,
                            WOLD_MAX_Y      = MAX_CHUNKS_Y * MAX_BLOCKS_Y,
                            WOLD_MAX_Z      = MAX_CHUNKS_Z * MAX_BLOCKS_Z,
                            CHUNK_VOLUME    = BLOCK_SIZE_X * MAX_BLOCKS_X * BLOCK_SIZE_Y * MAX_BLOCKS_Y * BLOCK_SIZE_Z * MAX_BLOCKS_Z,
                            CHUNK_AREA      = BLOCK_SIZE_X * MAX_BLOCKS_X * BLOCK_SIZE_Z * MAX_BLOCKS_Z;

    constexpr static int    MAX_LIGHT       = 10;
}



#endif //GAMEENGINE_WOLDCONST_H
