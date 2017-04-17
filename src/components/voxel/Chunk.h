//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_CHUNK_H
#define GAMEENGINE_CHUNK_H


#include "Block.h"
#include "World.h"
//16.4.2016 16*16*16 = 20FPS
//17.4.2016 16*16*16 = 40FPS
//17.4.2016 16*16*16 = 47FPS
//17.4.2016 16*16*16 = 50FPS
#define MAX_BLOCKS_X 16
#define MAX_BLOCKS_Y 16
#define MAX_BLOCKS_Z 16

#define CHUNK_SIZE_X (MAX_BLOCKS_X * BLOCK_SIZE_X * 2)
#define CHUNK_SIZE_Y (MAX_BLOCKS_Y * BLOCK_SIZE_Y * 2)
#define CHUNK_SIZE_Z (MAX_BLOCKS_Z * BLOCK_SIZE_Z * 2)

class Block;
class World;

class Chunk {
public:
    Chunk(int x, int y, int z, World * parent){
        this -> parent = parent;
        this -> x = x;
        this -> y = y;
        this -> z = z;
        generateAllBlocks();
        setUpNeigbors();
        setUpVisibility();
    };
    void setUpVisibility(void);
    void setUpNeigbors(void);
    static BlockType getRandomType(void);
    bool isTransparent(int x, int y, int z);
    inline Vector3f getOffsetPosition(void){return Vector3f(x, y, z); }
    inline Vector3f getAbsoulePosition(void){ return getSize() * getOffsetPosition(); }
    inline static Vector3f getSize(void){ return Vector3f(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z); }
    void cleanUp(void);
    inline World * getWorld(void){return parent;}
private:
    World * parent;
    int x, y, z;
    Block **** map;
    void generateAllBlocks(void);
    void generateBlock(int x, int y, int z);

};


#endif //GAMEENGINE_CHUNK_H