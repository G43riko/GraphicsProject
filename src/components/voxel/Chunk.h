//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_CHUNK_H
#define GAMEENGINE_CHUNK_H


//16.4.2016 16*16*16 = 20FPS
//17.4.2016 16*16*16 = 40FPS
//17.4.2016 16*16*16 = 47FPS
//17.4.2016 16*16*16 = 50FPS
//17.4.2016 64*16*64 = 10FPS
//23.4.2016 16*16*16 = 55FPS
//23.4.2016 64*16*64 = 11FPS
//23.4.2016 128*16*128 = 15FPS - všetky kocky


#include "WoldConst.h"
#include "Block.h"
#include "World.h"

class Block;
class World;

class Chunk {
public:
    Chunk(int x, int y, int z, World * parent) : parent(parent), x(x), y(y), z(z){
        generateAllBlocks();
    };

//    void setUpNeighbors(void){
//        setUpNeigbors();
//        setUpVisibility();
//    }
    void removeBlock(Vector3f position){return removeBlock(position.getXi(), position.getYi(), position.getZi()); };
    void removeBlock(int x, int y, int z);
    void show(void);
    void setBlock(Block * block, int x, int y, int z){
        if(x < 0 || y < 0 || z < 0 || x >= MAX_BLOCKS_X || y >= MAX_BLOCKS_Y || z >= MAX_BLOCKS_Z){
            return;
        }
        map[x][y][z] = block;
    }
    inline Block * getBlock(int x, int y, int z) const{
        if(x < 0 || y < 0 || z < 0 || x >= MAX_BLOCKS_X || y >= MAX_BLOCKS_Y || z >= MAX_BLOCKS_Z){
            return nullptr;
        }
        return map[x][y][z];
    }
    void setUpVisibility(void);
    void setUpNeigbors(void);
//    inline static BlockType getRandomType(void){
//        switch((int)random(1, 9)){
//            case 1: return BlockType::red;
//            case 2: return BlockType::aqua;
//            case 3: return BlockType::blue;
//            case 4: return BlockType::magenta;
//            case 5: return BlockType::yellow;
//            case 6: return BlockType::green;
//            case 8: return BlockType::black;
//            default: return BlockType::white;
//        }
//    }
    inline bool isTransparent(int x, int y, int z) const{
        //ak blok neexistuje tak je priehladný
        if(x < 0 || y < 0 || z < 0 || x >= MAX_BLOCKS_X || y >= MAX_BLOCKS_Y || z >= MAX_BLOCKS_Z){
            return true;
        }
        return getBlock(x, y, z) == nullptr ;//|| !map[x][y][z] -> isVisible();
    }
    inline Vector3f getOffsetPosition(void) const{return Vector3f(x, y, z); }
    inline Vector3f getAbsoulePosition(void) const{return getSize() * getOffsetPosition(); }
    inline static Vector3f getSize(void){return Vector3f(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z); }
    inline World * getWorld(void) const{return parent;}
    void cleanUp(void);
private:
    World * parent;
    const int x, y, z;
    Block **** map;
    void generateAllBlocks(void);
    void generateBlock(int x, int y, int z);

};


#endif //GAMEENGINE_CHUNK_H
