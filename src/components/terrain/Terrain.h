//
// Created by gabriel on 12.11.2016.
//

#ifndef GRAPHICSPROJECT_TERRAIN_H
#define GRAPHICSPROJECT_TERRAIN_H


#include <src/rendering/model/RawModel.h>
#include <src/rendering/material/Texture2D.h>
#include <src/utils/Loader.h>
#include <src/utils/math/objects/Vectors.h>
#include <src/rendering/model/MaterialedModel.h>
#include "HeightGenerator.h"

class Terrain {
public:
    inline ~Terrain(){
        clearMap();
    }
    inline Terrain(Loader loader, PointerTexture2D texture, GLuint size, GLuint vertices, float height, float textMulti, float **mapa = nullptr) :
            height(height),
            texture(texture),
            generator(HeightGenerator(height)),
            vertices(vertices),
            size(size){
        if(IS_NOT_NULL(mapa)){
            if(map){
                clearMap();
            }
            map = mapa;
        }
        else{
            initMap(vertices, vertices);
        }
        model = MaterialedModel::create(generateTerrain(loader, textMulti), Material::create(texture));
    }

    inline PointerMaterialedModel getModel(void) const{return model; }
    inline float getHeight(const int surX, const int surZ)const{return getTerrainHeight(surX, surZ); };

private:
    float ** map = nullptr;
    const float height;
    const PointerTexture2D texture;
    const HeightGenerator generator;
    const GLuint vertices;
    const GLuint size;
    PointerMaterialedModel model = nullptr;

    inline void clearMap(void){
        LOOP_U(vertices, i){
            delete[] map[i];
        }

        delete[] map;
    }

    inline void initMap(const GLuint x, const GLuint y){
        if(map){
            clearMap();
        }
        map = new float * [x];
        LOOP_U(x, i){
            map[i] = new float[y];
        }
    }

    inline Vector3f calculateNormal(const GLuint x, const GLuint z) const{
        const float heightL = getTerrainHeight(x - 1, z);
        const float heightR = getTerrainHeight(x + 1, z);
        const float heightD = getTerrainHeight(x, z - 1);
        const float heightU = getTerrainHeight(x, z + 1);
        return Vector3f(heightL - heightR, 2.0f, heightD - heightU).normalize();
    }

    inline float getTerrainHeight(const GLuint x, const GLuint z) const{
        if(x >= vertices || z >= vertices){
            return 0;
        }
        return map[x][z];
    }
    inline PointerRawModel generateTerrain(Loader loader, const float textMulti) const{
        VectorF verticesVector, normals, textures;
        VectorUI indices;

        const float premulSize = (float)size / (float)(vertices - 1);
        const float premulTexture = textMulti / (float)(vertices - 1);
        const uint premulVertices = vertices * vertices;
        //vygeneruje výškovú mapu pre terén a vypočíta súradnice pre textúru

        map[0][0] = generator.generateHeight(0, 0);
        LOOP_U(vertices, i){
            map[0][i] = generator.generateHeight(0, i);
            map[i][0] = generator.generateHeight(i, 0);
        }
        //vypočíta normály
        indices.reserve(premulVertices * 6);
        verticesVector.reserve(premulVertices * 3);
        textures.reserve(premulVertices * 2);
        normals.reserve(premulVertices * 3);
        LOOP_U(vertices, gz){
            LOOP_U(vertices, gx){
                if(gz < vertices - 1 && gx < vertices - 1){
                    map[gx + 1][gz + 1] = generator.generateHeight(gx + 1,  gz + 1);

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

                verticesVector.push_back((float)gx * premulSize);
                verticesVector.push_back(map[gx][gz]);
                verticesVector.push_back((float)gz * premulSize);

                textures.push_back((float)gx * premulTexture);
                textures.push_back((float)gz * premulTexture);


                const Vector3f normal = calculateNormal(gx, gz);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
            }
        }

        //vráti nový rawPointer
        return loader.loadToVao(verticesVector, textures, normals, indices);
    }
};


#endif //GRAPHICSPROJECT_TERRAIN_H
