//
// Created by gabriel on 16.4.2017.
//

#include "World.h"

World::World(BasicScene * scene, PointerRawModel model){
//    int sum = (WOLD_MAX_X * WOLD_MAX_Y * WOLD_MAX_Z);
//    PRINT("size: " << sum);
    this -> scene = scene;
    this -> model = model;
//    model1 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(255, 0, 0))));
//    model2 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(0, 255, 0))));
//    model3 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(0, 0, 255))));
//    model4 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(255, 255, 0))));
//    model5 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(0, 255, 255))));
//    model6 = createMaterialedModel(model, createMaterial(TextureManager::createTexture2D(Vector3f(255, 0, 255))));
    init();
    generateChunk(0, 0, 0);
}
void World::init(void){
    map = new Chunk *** [MAX_CHUNKS_X];
    for(int i=0 ; i< MAX_CHUNKS_X ; i++){
        map[i] = new Chunk ** [MAX_CHUNKS_Y];
        for(int j=0 ; j<MAX_CHUNKS_Y ; j++){
            map[i][j] = new Chunk * [MAX_CHUNKS_Z];
            for(int k=0 ; k<MAX_CHUNKS_Z ; k++){
                map[i][j][k] = nullptr;
            }
        }
    }
}
Block * World::getBlockOn(int x, int y, int z){
    if(x < 0 || y < 0 || z < 0 || x >= WOLD_MAX_X || y >= WOLD_MAX_Y || z >= WOLD_MAX_Z){
        return nullptr;
    }
    int chunkX = x / MAX_BLOCKS_X;
    int chunkY = y / MAX_BLOCKS_Y;
    int chunkZ = z / MAX_BLOCKS_Z;

    return getChunk(chunkX, chunkY, chunkZ) -> getBlock(x % MAX_BLOCKS_X, y % MAX_BLOCKS_Y, z % MAX_BLOCKS_Z);
}

void World::cleanUp(void){
    for(int i=0 ; i< MAX_CHUNKS_X ; i++){
        for(int j=0 ; j<MAX_CHUNKS_Y ; j++){
            for(int k=0 ; k<MAX_CHUNKS_Z ; k++){
                CHECK_AND_CLEAR(map[i][j][k]);
            }
            delete[] map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}
void World::generateChunk(int x, int y, int z){
    map[x][y][z] = new Chunk(x, y, z, this);
}