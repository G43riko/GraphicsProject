//
// Created by gabriel on 12.11.2016.
//

#ifndef GRAPHICSPROJECT_TERRAIN_H
#define GRAPHICSPROJECT_TERRAIN_H


#include <src/rendering/model/RawModel.h>
#include <src/rendering/material/Texture2D.h>
#include <src/utils/Loader.h>

class Terrain {
private:
    static constexpr float SIZE = 800;
    static constexpr float VERTEX_COUNT = 128;
    float x;
    float y;
    PointerRawModel rawModel;
    Texture2D texture;

public:
    Terrain(int gridX, int gridZ, Loader loader, Texture2D texture) : texture(texture), x(gridX * SIZE), y(gridZ * SIZE){
        rawModel = generateTerrain(loader);
    }

    PointerRawModel generateTerrain(Loader loader){
        int count = VERTEX_COUNT * VERTEX_COUNT;
        float * vertices = new float[count * 3];
        float * normals = new float[count * 3];
        float * textureCoords = new float[count*2];
        int number = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);
        GLuint * indices = new GLuint[number];
        int vertexPointer = 0;
        for(int i=0 ; i<VERTEX_COUNT ; i++){
            for(int j=0 ; j<VERTEX_COUNT ; j++){
                vertices[vertexPointer * 3] = (float)j / (VERTEX_COUNT - 1) * SIZE;
                vertices[vertexPointer * 3 + 1] = 0;
                vertices[vertexPointer * 3 + 2] = (float)i / (VERTEX_COUNT - 1) * SIZE;
                normals[vertexPointer * 3] = 0;
                normals[vertexPointer * 3 + 1] = 1;
                normals[vertexPointer * 3 + 2] = 0;
                textureCoords[vertexPointer * 2] = (float)j / (VERTEX_COUNT - 1);
                textureCoords[vertexPointer * 2 + 1] = (float)i / (VERTEX_COUNT - 1);
                vertexPointer++;
            }
        }
        int pointer = 0;
        for(int gz=0 ; gz<VERTEX_COUNT-1 ; gz++){
            for(int gx=0 ; gx<VERTEX_COUNT-1 ; gx++){
                int topLeft = (gz*VERTEX_COUNT)+gx;
                int topRight = topLeft + 1;
                int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
                int bottomRight = bottomLeft + 1;
                indices[pointer++] = topLeft;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = topRight;
                indices[pointer++] = topRight;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = bottomRight;
            }
        }
        PointerRawModel result = loader.loadToVaoA(vertices, textureCoords, normals, indices);
        delete[] vertices;
        delete[] normals;
        delete[] textureCoords;
        delete[] indices;
        return result;
    }

static float** create(int x2, int y2){
        mapa = new float * [x2];
        for(int i=0 ; i<x2 ; i++){
            mapa[i] = new float[y2];
        }
        mapa[0][0] 		        = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        mapa[0][y2 - 1]         = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        mapa[x2 - 1][0]         = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        mapa[x2 - 1][y2 - 1]    = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        generateMap(0, 0, x2 - 1, y2 - 1);

        return mapa;
    }
private:
    static float ** mapa;

static void generateMap(int x1, int y1, int x2, int y2) {
        float cl1 = mapa[x1][y1];
        float cl2 = mapa[x2][y1];
        float cl3 = mapa[x1][y2];
        float cl4 = mapa[x2][y2];
/*

        GVector2f b1 = new GVector2f((x1 + x2) / 2, y1);
        mapa[b1.getXi()][b1.getYi()] =  GMath.average(cl1, cl2);

        GVector2f b2 = new GVector2f((x1 + x2) / 2, y2);
        mapa[b2.getXi()][b2.getYi()] =  GMath.average(cl3, cl4);

        GVector2f b3 = new GVector2f(x1, (y1 + y2) / 2);
        mapa[b3.getXi()][b3.getYi()] =  GMath.average(cl1, cl3);

        GVector2f b4 = new GVector2f(x2, (y1 + y2) / 2);
        mapa[b4.getXi()][b4.getYi()] =  GMath.average(cl2, cl4);

        GVector2f b5 = new GVector2f((x1 + x2) / 2, (y1 + y2) / 2);
        mapa[b5.getXi()][b5.getYi()] =  GMath.average(cl1, cl2, cl3, cl4) + (float)(Math.random()-0.5);

        if(x2 - x1 <= 2 || y2 - y1 <= 2)
            return;

        generateMap(x1, y1, b5.getXi(), b5.getYi());
        generateMap(b1.getXi(), b1.getYi(), b4.getXi(), b4.getYi());
        generateMap(b3.getXi(), b3.getYi(), b2.getXi(), b2.getYi());
        generateMap(b5.getXi(), b5.getYi(), x2, y2);
*/
    }
};


#endif //GRAPHICSPROJECT_TERRAIN_H
