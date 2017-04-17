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

    Terrain(Loader loader, PointerTexture2D texture, GLuint size, int vertices, float height, int textMulti, float **mapa)
            : map(mapa),
              height(height),
              texture(texture),
              generator(HeightGenerator(height)),
              vertices(vertices),
              size(size){
        std::vector<float> verticesVector, normals, textures;
        std::vector<GLuint> indices;
        for(unsigned int i=0 ; i<vertices ; i++){
            for(unsigned int j=0 ; j<vertices ; j++){

                verticesVector.push_back((float)j / (vertices - 1) * size);
                verticesVector.push_back(mapa[j][i]);
                verticesVector.push_back((float)i / (vertices - 1) * size);

                textures.push_back((float)j / (vertices - 1) * textMulti);
                textures.push_back((float)i / (vertices - 1) * textMulti);
            }
        }
        //vypočíta normály
        for(unsigned int gz=0 ; gz<vertices ; gz++){
            for(unsigned int gx=0 ; gx<vertices ; gx++){
                Vector3f normal = calculateNormal(gx, gz);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
                if(gz < vertices - 1 && gx < vertices - 1){
                    GLuint topLeft = gz * vertices + gx;
                    GLuint topRight = topLeft + 1;
                    GLuint bottomLeft = (gz + 1) * vertices + gx;
                    GLuint bottomRight = bottomLeft + 1;

                    indices.push_back(topLeft);
                    indices.push_back(bottomLeft);
                    indices.push_back(topRight);
                    indices.push_back(topRight);
                    indices.push_back(bottomLeft);
                    indices.push_back(bottomRight);
                }
            }
        }

        //vráti nový rawPointer
        model = createMaterialedModel(loader.loadToVao(verticesVector, textures, normals, indices),  createMaterial(texture));
    }
    Terrain(Loader loader, PointerTexture2D texture, GLuint size, int vertices, float height, int textures)
            : height(height),
              texture(texture),
              generator(HeightGenerator(height)),
              vertices(vertices),
              size(size){
        initMap(vertices, vertices);
        model = createMaterialedModel(generateTerrain(loader, textures), createMaterial(texture));
    }

    PointerMaterialedModel getModel() {
        return model;
    }
    float getHeight(int surX, int surZ){
//        PRINT("surX: " << surX << ", surZ: "<< surZ << ", height: " << getTerrainHeight(surX , surZ) * height);
        return getTerrainHeight(surX, surZ) ;
    };

private:
    float ** map = nullptr;
    float height;
    PointerTexture2D texture;
    HeightGenerator generator;
    int vertices;
    GLuint size;
    PointerMaterialedModel model;

    void clearMap(){
        for(int i=0 ; i<vertices ; i++){
            delete[] map[i];
        }
        delete[] map;
    }

    void initMap(unsigned int x, unsigned int y){
        if(map){
            clearMap();
        }
        map = new float * [x];
        for(unsigned int i=0 ; i<x; i++){
            map[i] = new float[y];
        }
    }

    float getTerrainHeight(int x, int z);
    Vector3f calculateNormal(int x, int z);
    PointerRawModel generateTerrain(Loader loader, int textMulti);
};


#endif //GRAPHICSPROJECT_TERRAIN_H
