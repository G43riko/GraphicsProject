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
#include "World_old.h"

class Block;
class World_old;

class Chunk_old {
public:
    Chunk_old(int x, int y, int z, World_old * parent) : parent(parent), x(x), y(y), z(z){
        generateAllBlocks();
    };

//    void setUpNeighbors(void){
//        setUpNeigbors();
//        setUpVisibility();
//    }
    void removeBlock(Vector3f position){return removeBlock(position.getXi(), position.getYi(), position.getZi()); };
    void removeBlock(int x, int y, int z);
    void show(void);
    void setBlock(Block * block, unsigned int x, unsigned int y, unsigned int z){
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE){
            return;
        }
        map[x][y][z] = block;
    }
    inline Block * getBlock(int x, int y, int z) const{
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE){
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
    inline bool isTransparent(unsigned int x, unsigned int y, unsigned int z) const{
        //ak blok neexistuje tak je priehladný
        if(x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE){
            return true;
        }
        return getBlock(x, y, z) == nullptr ;//|| !map[x][y][z] -> isVisible();
    }
    inline Vector3f getOffsetPosition(void) const{return Vector3f(x, y, z); }
    inline Vector3f getAbsoulePosition(void) const{return getSize() * getOffsetPosition(); }
    inline static Vector3f getSize(void){return Vector3f(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE); }
    inline World_old * getWorld(void) const{return parent;}
    void cleanUp(void);
private:
    World_old * parent;
    const int x, y, z;
    Block **** map;
    void generateAllBlocks(void);
    void generateBlock(int x, int y, int z);

};


#endif //GAMEENGINE_CHUNK_H
