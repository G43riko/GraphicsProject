//
// Created by gabriel on 16.4.2017.
//

#include "Chunk.h"
#include "BlockTypes.h"


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
                else{
                    Chunk * chunk = parent->getChunk(x - 1, y, z);
                    if(IS_NOT_NULL(chunk)){
                        map[i][j][k] -> setNeighbor(chunk -> map[MAX_BLOCKS_X - 1][j][k]);
                    }
                }
                if(j > 0){
                    map[i][j][k] -> setNeighbor(map[i][j - 1][k]);
                }
                else{
                    Chunk * chunk = parent->getChunk(x, y - 1, z);
                    if(IS_NOT_NULL(chunk)){
                        map[i][j][k] -> setNeighbor(chunk -> map[i][MAX_BLOCKS_Y - 1][k]);

                    }
                }
                if(k > 0) {
                    map[i][j][k]->setNeighbor(map[i][j][k - 1]);
                }
                else{
                    Chunk * chunk = parent->getChunk(x, y, z - 1);
                    if(IS_NOT_NULL(chunk)){
                        map[i][j][k] -> setNeighbor(chunk -> map[i][j][MAX_BLOCKS_Z - 1]);

                    }
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
void Chunk::removeBlock(int x, int y, int z){
    Block * b = getBlock(x, y, z);
    for (auto it = parent->blocks.begin(); it != parent->blocks.end(); ){
        if((*it) == b){
            it = parent->blocks.erase(it);
        }
        else{
            ++it;
        }
    }
    b -> cleanUp();
    delete b;
    setBlock(nullptr, x, y, z);
}
void Chunk::show(void){
    for(int i=0 ; i< MAX_BLOCKS_X ; i++) {
        for (int j = 0; j < MAX_BLOCKS_Y; j++) {
            for (int k = 0; k < MAX_BLOCKS_Z; k++) {
                if(IS_NOT_NULL(map[i][j][k])){
                    printf("%d_%d_%d = ",  i, j ,k);
                    map[i][j][k] -> show();
                }
                else{
                    printf("%d_%d_%d = null\n", i, j ,k);
                }
            }
        }
    }
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
    if(grandom(0, 5) > 1){
        //setBlock(new Block(x, y, z, this, getRandomType()), x, y, z);
        setBlock(new Block(x, y, z, this, BlockTypes::getRandomType()), x, y, z);
    }
    else{
        setBlock(nullptr, x, y, z);
    }
}