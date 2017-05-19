//
// Created by gabriel on 16.4.2017.
//

#include "World_old.h"

World_old::World_old(BasicScene * scene, PointerRawModel planeModel, PointerRawModel boxModel){
//    int sum = (WOLD_MAX_X * WOLD_MAX_Y * WOLD_MAX_Z);
//    PRINT("size: " << sum);
    this -> scene = scene;
    this -> model = planeModel;
    this -> boxModel = boxModel;
//    model1 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(255, 0, 0))));
//    model2 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(0, 255, 0))));
//    model3 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(0, 0, 255))));
//    model4 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(255, 255, 0))));
//    model5 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(0, 255, 255))));
//    model6 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(255, 0, 255))));
    double initTime = glfwGetTime();;
    init();
    //generateChunks(0, 0, 0, 5, 1, 5);
    generateChunk(0, 0, 0);
    setUpNeighbors();
    printf("%ld kociek sa vytvorilo za %f \n", blocks.size(), glfwGetTime() - initTime);
}
void World_old::init(void){
    map = new Chunk_old *** [WORLD_SIZE];
    for(int i=0 ; i< WORLD_SIZE ; i++){
        map[i] = new Chunk_old ** [WORLD_SIZE];
        for(int j=0 ; j<WORLD_SIZE ; j++){
            map[i][j] = new Chunk_old * [WORLD_SIZE];
            for(int k=0 ; k<WORLD_SIZE ; k++){
                map[i][j][k] = nullptr;
            }
        }
    }
}

void World_old::show(void){
    for(int i=0 ; i< WORLD_SIZE ; i++){
        for(int j=0 ; j<WORLD_SIZE ; j++){
            for(int k=0 ; k<WORLD_SIZE ; k++){
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
Block * World_old::getBlockOn(int x, int y, int z){
    if(x < 0 || y < 0 || z < 0 || x >= WOLD_MAX || y >= WOLD_MAX || z >= WOLD_MAX){
        return nullptr;
    }
    x /= 2;
    y /= 2;
    z /= 2;
    int chunkX = x / CHUNK_SIZE;
    int chunkY = y / CHUNK_SIZE;
    int chunkZ = z / CHUNK_SIZE;

    return getChunk(chunkX, chunkY, chunkZ) -> getBlock(x % REAL_CHUNK_SIZE, y % REAL_CHUNK_SIZE, z % REAL_CHUNK_SIZE);
}
void World_old::setUpNeighbors(void){
    for(int i=0 ; i< WORLD_SIZE ; i++){
        for(int j=0 ; j<1 ; j++){
            for(int k=0 ; k<WORLD_SIZE ; k++){
                if(IS_NOT_NULL(map[i][j][k])){
                    map[i][j][k]->setUpNeigbors();
                }
            }
        }
    }
}
void World_old::cleanUp(void){
    for(int i=0 ; i< WORLD_SIZE ; i++){
        for(int j=0 ; j<1 ; j++){
            for(int k=0 ; k<WORLD_SIZE ; k++){
                CHECK_AND_CLEAR(map[i][j][k]);
            }
            delete[] map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}
void World_old::generateChunk(int x, int y, int z){
    map[x][y][z] = new Chunk_old(x, y, z, this);
}