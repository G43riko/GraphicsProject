//
// Created by gabriel on 16.4.2017.
//

#include "World.h"

World::World(BasicScene * scene, PointerRawModel model){
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