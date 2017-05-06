//
// Created by gabriel on 13.4.2017.
//

#ifndef GRAPHICSPROJECT_TERRAINMANAGER_H
#define GRAPHICSPROJECT_TERRAINMANAGER_H


#include <src/core/BasicScene.h>
#include <map>
#include "Terrain.h"
#define DEFAULT_HEIGHT 0
#define VERTICAL_OFFSET 1.0f
#define MAP_CONTAINS_KEY(map, key) (map.find(key) != map.end())

class TerrainManager {
private:
    std::map<int, Terrain *> terrains;
    float size;
    Loader loader;
    BasicScene * scene = nullptr;
    int hash(int x, int z){
        int k1 = x >= 0 ? x * 2 : -x * 2 - 1;
        int k2 = z >= 0 ? z * 2 : -z * 2 - 1;
        return (k1 + k2) * (k1 + k2 + 1) / 2 + k1;
    }
    public:
        TerrainManager(Loader loader, GLuint size, BasicScene * scene) : size((float)size), loader(loader), scene(scene){
//            for(int i=0 ; i<10 ; i++){
//                for(int j=0 ; j<10 ; j++){
//                    PRINT("hash (" << i << ", " << j << " je: " << hash(i, j));
//                }
//            }
        };

        void generateTerrain(PointerTexture2D texture, int vertices, float height, int textures, int posX, int posZ){
            Terrain * t = new Terrain(loader,
                                texture,
                                (unsigned int)size,
                                vertices,
                                height,
                                textures);

            scene -> addEntity(createEntity(t -> getModel(),
                                            Vector3f((float)posX * size, VERTICAL_OFFSET, (float)posZ * size),
                                            Vector3f(0.0f, 0.0f, 0.0f),
                                            Vector3f(1.0f, 1.0f, 1.0f)));

//            float **map;
//            map = new float * [vertices];
//            for(unsigned int i=0 ; i<(unsigned int)vertices ; i++) {
//                map[i] = new float[vertices];
//                for (unsigned int j = 0; j < (unsigned int)vertices; j++) {
//                    map[i][j] = t->getHeight(i, j);
//                }
//            }
//            Terrain * t2 = new Terrain(loader,
//                                      texture,
//                                       (unsigned int)size,
//                                      vertices,
//                                      height,
//                                      textures, map);
//
//            scene -> addEntity(createEntity(t2 -> getModel(),
//                                            Vector3f((float)posX * size, 0.0f, (float)posZ * size),
//                                            Vector3f(0.0f, 0.0f, 0.0f),
//                                            Vector3f(1.0f, 1.0f, 1.0f)));

            PRINT("terrain: [" << posX << ", " << posZ);
            terrains[hash(posX, posZ)] = t;
        }

        float modulo(float x, float y){
            //float result = fmod(x, y);
            if(x < 0){
                //x += y;
                x *= -1;
            }
            return x;
        }
        float getHeight(float x, float z){
            int surX = (int)(x / size);
            int surZ = (int)(z / size);
            float posX = ((x - (float)surX * size) / size);
            float posZ = ((z - (float)surZ * size) / size);
            int hashVal = hash((int)floor(posX), (int)floor(posZ));
            if(!MAP_CONTAINS_KEY(terrains, hashVal)){
                return DEFAULT_HEIGHT;
            }

            return terrains[hashVal] -> getHeight((int)(x * 128 / size), (int)(z * 128 / size)) + VERTICAL_OFFSET;
        }

        void cleanUp(void){
            //vymažeme všetky terény
            for(auto terrain : terrains){
                delete terrain . second;
            }
            //vyčistíme mapu terénov
            terrains.clear();
        };
};


#endif //GRAPHICSPROJECT_TERRAINMANAGER_H
