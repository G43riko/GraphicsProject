//
// Created by gabriel on 16.4.2017.
//

#include "Chunk.h"
BlockType Chunk::getRandomType(void){
    switch((int)random(1, 9)){
        case 1: return BlockType::red;
        case 2: return BlockType::aqua;
        case 3: return BlockType::blue;
        case 4: return BlockType::magenta;
        case 5: return BlockType::yellow;
        case 6: return BlockType::green;
        case 8: return BlockType::black;
        default: return BlockType::white;
    }
}

void Chunk::setUpNeigbors(void){
    for(int i=0 ; i<MAX_BLOCKS_X ; i++){
        for(int j=0 ; j<MAX_BLOCKS_Y ; j++){
            for(int k=0 ; k<MAX_BLOCKS_Z ; k++){
                if(map[i][j][k] == nullptr){
                    continue;
                }
                if(i > 0){
                    map[i][j][k] -> setNeighbor(map[i - 1][j][k]);
                }
                if(j > 0){
                    map[i][j][k] -> setNeighbor(map[i][j - 1][k]);
                }
                if(k > 0){
                    map[i][j][k] -> setNeighbor(map[i][j][k - 1]);
                }
            }
        }
    }
}
void Chunk::setUpVisibility(void){
    for(int i=0 ; i<MAX_BLOCKS_X ; i++){
        for(int j=0 ; j<MAX_BLOCKS_Y ; j++){
            for(int k=0 ; k<MAX_BLOCKS_Z ; k++){
                if(map[i][j][k]){
                    map[i][j][k] -> setUpVisibility();
                }
            }
        }
    }
}
void Chunk::cleanUp(void){
    for(int i=0 ; i< MAX_BLOCKS_X ; i++){
        for(int j=0 ; j<MAX_BLOCKS_Y ; j++){
            for(int k=0 ; k<MAX_BLOCKS_Z ; k++){
                CHECK_AND_CLEAR(map[i][j][k]);
            }
            delete[] map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}
bool Chunk::isTransparent(int x, int y, int z){
    //ak blok neexistuje tak je priehladný
    if(x < 0 || y < 0 || z < 0 || x >= MAX_BLOCKS_X || y >= MAX_BLOCKS_Y || z >= MAX_BLOCKS_Z){
        return true;
    }
    return map[x][y][z] == nullptr ;//|| !map[x][y][z] -> isVisible();
}
void Chunk::generateAllBlocks(void){
    map = new Block *** [MAX_BLOCKS_X];
    for(int i=0 ; i< MAX_BLOCKS_X ; i++){
        map[i] = new Block ** [MAX_BLOCKS_Y];
        for(int j=0 ; j<MAX_BLOCKS_Y ; j++){
            map[i][j] = new Block * [MAX_BLOCKS_Z];
            for(int k=0 ; k<MAX_BLOCKS_Z ; k++){
                    generateBlock(i, j, k);
            }
        }
    }
}

void Chunk::generateBlock(int x, int y, int z){
    if(random(0, 5) > 1){
        map[x][y][z] = new Block(x, y, z, this, getRandomType());
    }
    else{
        map[x][y][z] = nullptr;
    }
}