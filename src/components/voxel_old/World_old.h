//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H


#include "WoldConst.h"

#include <src/utils/math/objects/Vectors.h>
#include <src/core/BasicScene.h>
#include <src/rendering/material/TextureManager.h>
#include "Chunk_old.h"

class Chunk_old;
class Block;
class World_old {
public:
    std::vector<Block*> blocks;
    World_old(BasicScene * scene, PointerRawModel planeModel, PointerRawModel boxModel);
    Chunk_old **** map = nullptr;
    void init(void);
    void cleanUp(void);

    void show(void);
    Block * getBlockOn(int x, int y, int z);
    inline PointerMaterialedModel getModel(int number){
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
    inline PointerRawModel getModel(void)const {return model; }
    inline PointerRawModel getBoxModel(void)const {return boxModel; }
    inline BasicScene * getScene(void) const{return scene;}
    Chunk_old * getChunk(int x, int y, int z)const {
        if(x < 0 || y < 0 || z < 0 || x >= WORLD_SIZE || y >= WORLD_SIZE || z >= WORLD_SIZE){
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

    inline void generateChunks(int minX, int minY, int minZ, int maxX, int maxY, int maxZ){
        for(int i=minX ; i<maxX ; i++){
            for(int j=minY ; j<maxY ; j++){
                for(int k=minZ ; k<maxZ ; k++){
                    generateChunk(i, j, k);
                }
            }
        }
    }
    void generateChunk(int x, int y, int z);
};


#endif //GAMEENGINE_WORLD_H
