//
// Created by gabriel on 12.11.2016.
//

#ifndef GRAPHICSPROJECT_TERRAIN_H
#define GRAPHICSPROJECT_TERRAIN_H


#include <src/rendering/model/RawModel.h>
#include <src/rendering/material/Texture2D.h>
#include <src/utils/Loader.h>
#include <src/utils/Vectors.h>
#include <src/rendering/model/MaterialedModel.h>
#include "HeightGenerator.h"

class Terrain {
public:
    ~Terrain(){
        clearMap();
    }
    Terrain(Loader loader, PointerTexture2D texture, GLuint size, int vertices, float height, int textures) : texture(texture), generator(HeightGenerator(height)){
        initMap(vertices, vertices);
        this -> vertices = vertices;
        this -> size = size;
        PointerRawModel m = generateTerrain(loader, textures);
        model = createMaterialedModel(m, createMaterial(texture));


    }

    PointerMaterialedModel getModel() {
        return model;
    }
    float getHeight(int surX, int surZ){

        return getTerrainHeight(surX / size, surZ / size);
    };

private:
    GLuint size;
    void clearMap(){
        for(unsigned int i=0 ; i<vertices ; i++)
            delete[] map[i];
        delete[] map;
    }

    void initMap(int x, int y){
        if(map){
            clearMap();
        }
        map = new float * [x];
        for(unsigned int i=0 ; i<x; i++)
            map[i] = new float[y];
    }
    int vertices;
    float ** map = nullptr;
    PointerTexture2D texture;
    HeightGenerator generator;
    PointerMaterialedModel model;
    float getTerrainHeight(int x, int z);
    Vector3f calculateNormal(int x, int z);
    PointerRawModel generateTerrain(Loader loader, int textMulti);
};


#endif //GRAPHICSPROJECT_TERRAIN_H
