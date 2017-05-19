//
// Created by gabriel on 16.4.2017.
//

#include "Chunk_old.h"
#include "BlockTypes.h"


void Chunk_old::setUpNeigbors(void){
    for(int i=0 ; i<CHUNK_SIZE ; i++){
        for(int j=0 ; j<CHUNK_SIZE ; j++){
            for(int k=0 ; k<CHUNK_SIZE ; k++){
                if(map[i][j][k] == nullptr){
                    continue;
                }
                if(i > 0){
                    map[i][j][k] -> setNeighbor(map[i - 1][j][k]);
                }
                else{
                    Chunk_old * chunk = parent->getChunk(x - 1, y, z);
                    if(IS_NOT_NULL(chunk)){
                        map[i][j][k] -> setNeighbor(chunk -> map[CHUNK_SIZE - 1][j][k]);
                    }
                }
                if(j > 0){
                    map[i][j][k] -> setNeighbor(map[i][j - 1][k]);
                }
                else{
                    Chunk_old * chunk = parent->getChunk(x, y - 1, z);
                    if(IS_NOT_NULL(chunk)){
                        map[i][j][k] -> setNeighbor(chunk -> map[i][CHUNK_SIZE - 1][k]);

                    }
                }
                if(k > 0) {
                    map[i][j][k]->setNeighbor(map[i][j][k - 1]);
                }
                else{
                    Chunk_old * chunk = parent->getChunk(x, y, z - 1);
                    if(IS_NOT_NULL(chunk)){
                        map[i][j][k] -> setNeighbor(chunk -> map[i][j][CHUNK_SIZE - 1]);

                    }
                }
            }
        }
    }
}
void Chunk_old::setUpVisibility(void){
    for(int i=0 ; i<CHUNK_SIZE ; i++){
        for(int j=0 ; j<CHUNK_SIZE ; j++){
            for(int k=0 ; k<CHUNK_SIZE ; k++){
                if(map[i][j][k]){
                    map[i][j][k] -> setUpVisibility();
                }
            }
        }
    }
}
void Chunk_old::cleanUp(void){
    for(int i=0 ; i< CHUNK_SIZE ; i++){
        for(int j=0 ; j<CHUNK_SIZE ; j++){
            for(int k=0 ; k<CHUNK_SIZE ; k++){
                CHECK_AND_CLEAR(map[i][j][k]);
            }
            delete[] map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}
void Chunk_old::removeBlock(int x, int y, int z){
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
void Chunk_old::show(void){
    for(int i=0 ; i< CHUNK_SIZE ; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            for (int k = 0; k < CHUNK_SIZE; k++) {
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


void Chunk_old::generateAllBlocks(void){
    map = new Block *** [CHUNK_SIZE];
    for(int i=0 ; i< CHUNK_SIZE ; i++){
        map[i] = new Block ** [CHUNK_SIZE];
        for(int j=0 ; j<CHUNK_SIZE ; j++){
            map[i][j] = new Block * [CHUNK_SIZE];
            for(int k=0 ; k<CHUNK_SIZE ; k++){
                    generateBlock(i, j, k);
            }
        }
    }
}

void Chunk_old::generateBlock(int x, int y, int z){
    if(grandom(0, 5) > 1){
        //setBlock(new Block(x, y, z, this, getRandomType()), x, y, z);
        setBlock(new Block(x, y, z, this, BlockTypes::getRandomType()), x, y, z);
    }
    else{
        setBlock(nullptr, x, y, z);
    }
}