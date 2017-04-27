//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H


#define MAX_CHUNKS_X 3
#define MAX_CHUNKS_Y 3
#define MAX_CHUNKS_Z 3

#include <src/utils/Vectors.h>
#include <src/core/BasicScene.h>
#include <src/rendering/material/TextureManager.h>
#include "Chunk.h"

#define WOLD_MAX_X (MAX_CHUNKS_X * MAX_BLOCKS_X)
#define WOLD_MAX_Y (MAX_CHUNKS_Y * MAX_BLOCKS_Y)
#define WOLD_MAX_Z (MAX_CHUNKS_Z * MAX_BLOCKS_Z)


class Chunk;
class Block;
class World {
public:
    std::vector<Block*> blocks;
    World(BasicScene * scene, PointerRawModel planeModel, PointerRawModel boxModel);
    Chunk **** map = nullptr;
    void init(void);
    void cleanUp(void);
    inline BasicScene * getScene(void){return scene;}
    void show(void);
    Block * getBlockOn(int x, int y, int z);
    PointerMaterialedModel getModel(int number){
        switch(number){
            case 1: return model1;
            case 2: return model2;
            case 3: return model3;
            case 4: return model4;
            case 5: return model5;
            case 6: return model6;
            default: return model6;
        }
    }
    inline PointerRawModel getModel(void){return model; }
    inline PointerRawModel getBoxModel(void){return boxModel; }
    Chunk * getChunk(int x, int y, int z){
        if(x < 0 || y < 0 || z < 0 || x >= MAX_CHUNKS_X || y >= MAX_CHUNKS_Y || z >= MAX_CHUNKS_Z){
            return nullptr;
        }
        return map[x][y][z];
    }
private:

    void setUpNeighbors(void);
    PointerMaterialedModel model1, model2, model3, model4, model5, model6;
    PointerRawModel model;
    PointerRawModel boxModel;
    BasicScene * scene = nullptr;



    void generateChunks(Vector3f from, Vector3f to){

    }
    void generateChunk(int x, int y, int z);
};


#endif //GAMEENGINE_WORLD_H
