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
    Terrain(int gridX, int gridZ, Loader loader, PointerTexture2D texture, GLuint size, int vertices, float height, int textures) : texture(texture), x(gridX * size), z(gridZ * size), generator(HeightGenerator(height)){
        float ** map = new float * [vertices];
        for(unsigned int i=0 ; i<vertices ; i++)
            map[i] = new float[vertices];

        PointerRawModel m = generateTerrain(loader, map, size, vertices, textures);
        model = createMaterialedModel(m, createMaterial(texture));

        for(unsigned int i=0 ; i<vertices ; i++)
            delete[] map[i];
        delete[] map;
    }

    PointerMaterialedModel getModel() {
        return model;
    }

private:
    static float ** mapa;
    PointerTexture2D texture;
    HeightGenerator generator;
    float x;
    float z;
    PointerMaterialedModel model;
    float getHeight(int x, int z, float ** map, int size);
    Vector3f calculateNormal(int x, int z, float ** map, int size);
    PointerRawModel generateTerrain(Loader loader, float ** map, GLuint size, int vertexCount, int textMulti);
};


#endif //GRAPHICSPROJECT_TERRAIN_H
