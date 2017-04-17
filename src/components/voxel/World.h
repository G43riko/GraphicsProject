//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H


#include <src/utils/Vectors.h>
#include <src/core/BasicScene.h>
#include <src/rendering/material/TextureManager.h>
#include "Chunk.h"

#define MAX_CHUNKS_X 10
#define MAX_CHUNKS_Y 10
#define MAX_CHUNKS_Z 10

class Chunk;
class Block;
class World {
public:
    std::vector<Block*> blocks;
    World(BasicScene * scene, PointerRawModel model);
    Chunk **** map = nullptr;
    void init(void);
    void cleanUp(void);
    inline BasicScene * getScene(void){return scene;}

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
private:
    PointerMaterialedModel model1, model2, model3, model4, model5, model6;
    PointerRawModel model;
    BasicScene * scene = nullptr;
    Chunk * getChunk(int x, int y, int z){
        return map[x][y][z];
    }


    void generateChunks(Vector3f from, Vector3f to){

    }
    void generateChunk(int x, int y, int z);
};


#endif //GAMEENGINE_WORLD_H
