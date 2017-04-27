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
    inline ~Terrain(){
        clearMap();
    }

    inline Terrain(Loader loader, PointerTexture2D texture, GLuint size, int vertices, float height, int textMulti, float **mapa)
            : map(mapa),
              height(height),
              texture(texture),
              generator(HeightGenerator(height)),
              vertices(vertices),
              size(size){
        std::vector<float> verticesVector, normals, textures;
        std::vector<GLuint> indices;
        for(unsigned int i=0 ; i<(unsigned int)vertices ; i++){
            for(unsigned int j=0 ; j<(unsigned int)vertices ; j++){

                verticesVector.push_back((float)j / ((float)vertices - 1) * (float)size);
                verticesVector.push_back(mapa[j][i]);
                verticesVector.push_back((float)i / ((float)vertices - 1) * (float)size);

                textures.push_back((float)j / ((float)vertices - 1) * (float)textMulti);
                textures.push_back((float)i / ((float)vertices - 1) * (float)textMulti);
            }
        }
        //vypočíta normály
        for(unsigned int gz=0 ; gz<(unsigned int)vertices ; gz++){
            for(unsigned int gx=0 ; gx<(unsigned int)vertices ; gx++){
                Vector3f normal = calculateNormal(gx, gz);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
                if(gz < (unsigned int)vertices - 1 && gx < (unsigned int)vertices - 1){
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
    Terrain(Loader loader,const PointerTexture2D texture, const GLuint size, const int vertices, const float height, const int textures)
            : height(height),
              texture(texture),
              generator(HeightGenerator(height)),
              vertices(vertices),
              size(size){
        initMap((unsigned int)vertices, (unsigned int)vertices);
        model = createMaterialedModel(generateTerrain(loader, textures), createMaterial(texture));
    }

    inline PointerMaterialedModel getModel(void) const{return model; }
    inline float getHeight(const int surX, const int surZ)const{return getTerrainHeight(surX, surZ); };

private:
    float ** map = nullptr;
    const float height;
    const PointerTexture2D texture;
    const HeightGenerator generator;
    const int vertices;
    const GLuint size;
    PointerMaterialedModel model = nullptr;

    inline void clearMap(void){
        for(int i=0 ; i<vertices ; i++){
            delete[] map[i];
        }
        delete[] map;
    }

    inline void initMap(const unsigned int x, const unsigned int y){
        if(map){
            clearMap();
        }
        map = new float * [x];
        for(unsigned int i=0 ; i<x; i++){
            map[i] = new float[y];
        }
    }

    inline Vector3f calculateNormal(const int x, const int z) const{
        float heightL = getTerrainHeight(x - 1, z);
        float heightR = getTerrainHeight(x + 1, z);
        float heightD = getTerrainHeight(x, z - 1);
        float heightU = getTerrainHeight(x, z + 1);
        return Vector3f(heightL - heightR, 2.0f, heightD - heightU).normalize();
    }

    inline float getTerrainHeight(const int x, const int z) const{
        if(x < 0 || z < 0 || x >= vertices || z >= vertices){
            return 0;
        }
        float height = map[x][z];
        return height;
    }
    inline PointerRawModel generateTerrain(Loader loader,const int textMulti) const{
        std::vector<float> verticesVector, normals, textures;
        std::vector<GLuint> indices;

        //vygeneruje výškovú mapu pre terén a vypočíta súradnice pre textúru
        for(unsigned int i=0 ; i<(unsigned int)vertices ; i++){
            for(unsigned int j=0 ; j<(unsigned int)vertices ; j++){
                map[j][i] = generator.generateHeight(j, i);

                verticesVector.push_back((float)j / ((float)vertices - 1) * (float)size);
                verticesVector.push_back(map[j][i]);
                verticesVector.push_back((float)i / ((float)vertices - 1) * (float)size);

                textures.push_back((float)j / ((float)vertices - 1) * (float)textMulti);
                textures.push_back((float)i / ((float)vertices - 1) * (float)textMulti);
            }
        }
        PRINT(map[0][0] << ", " << map[10][0] << ", " << map[0][10] << ", " << map[10][10]);
        PRINT(map[0][0] << ", " << map[20][0] << ", " << map[0][20] << ", " << map[20][20]);
        PRINT(map[0][0] << ", " << map[30][0] << ", " << map[0][30] << ", " << map[30][30]);

        //vypočíta normály
        for(unsigned int gz=0 ; gz<(unsigned int)vertices ; gz++){
            for(unsigned int gx=0 ; gx<(unsigned int)vertices ; gx++){
                Vector3f normal = calculateNormal(gx, gz);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
                if(gz < (unsigned int)vertices - 1 && gx < (unsigned int)vertices - 1){
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
        return loader.loadToVao(verticesVector, textures, normals, indices);
    }
};


#endif //GRAPHICSPROJECT_TERRAIN_H
