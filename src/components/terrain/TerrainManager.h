//
// Created by gabriel on 13.4.2017.
//

#ifndef GRAPHICSPROJECT_TERRAINMANAGER_H
#define GRAPHICSPROJECT_TERRAINMANAGER_H


#include <src/core/BasicScene.h>
#include <map>
#include "Terrain.h"


class TerrainManager {
    std::map<int, Terrain *> terrains;
    const float size;
    Loader loader;
    BasicScene * scene = nullptr;

    inline int hash(int x, int z){
        const int k1 = x >= 0 ? x * 2 : -x * 2 - 1;
        const int k2 = z >= 0 ? z * 2 : -z * 2 - 1;
        return (k1 + k2) * (k1 + k2 + 1) / 2 + k1;
    }
public:
    inline TerrainManager(Loader loader, GLuint size, BasicScene * scene) :
            size((float)size),
            loader(loader),
            scene(scene){};

    inline void generateTerrain(PointerTexture2D texture,
                         GLuint vertices,
                         float height,
                         float textures,
                         int posX,
                         int posZ){
        Terrain * t = new Terrain(loader,
                                  texture,
                                  (uint)size,
                                  vertices,
                                  height,
                                  textures);

        scene -> addEntity(Entity::create(t -> getModel(),
                                          Vector3f((float)posX * size,
                                                   VERTICAL_TERRAIN_OFFSET,
                                                   (float)posZ * size),
                                          Vector3f(0.0f, 0.0f, 0.0f),
                                          Vector3f(1.0f, 1.0f, 1.0f)));

        terrains[hash(posX, posZ)] = t;
    }

    inline float modulo(float x, float y){
        //float result = fmod(x, y);
        if(x < 0){
            //x += y;
            x *= -1;
        }
        return x;
    }
    inline float getHeight(float x, float z){
        const int surX = (int)(x / size);
        const int surZ = (int)(z / size);
        const float posX = ((x - (float)surX * size) / size);
        const float posZ = ((z - (float)surZ * size) / size);
        const int hashVal = hash((int)floor(posX), (int)floor(posZ));

        if(!MAP_CONTAINS_KEY(terrains, hashVal)){
            return DEFAULT_TERRAIN_HEIGHT;
        }

        return terrains[hashVal] -> getHeight((int)(x * 128 / size), (int)(z * 128 / size)) + VERTICAL_TERRAIN_OFFSET;
    }

    inline void cleanUp(void){
        //vymažeme všetky terény
        ITERATE_MAP_AUTO(terrains, it){
            delete it -> second;
        }
        //vyčistíme mapu terénov
        terrains.clear();
    };
};


#endif //GRAPHICSPROJECT_TERRAINMANAGER_H
