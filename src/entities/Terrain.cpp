//
// Created by gabriel on 12.11.2016.
//

#include "Terrain.h"

Vector3f Terrain::calculateNormal(int x, int z, float ** map, int size){
    float heightL = getHeight(x - 1, z, map, size);
    float heightR = getHeight(x + 1, z, map, size);
    float heightD = getHeight(x, z - 1, map, size);
    float heightU = getHeight(x, z + 1, map, size);
    Vector3f normal = Vector3f(heightL - heightR, 2.0f, heightD - heightU);
    normal.normalize();
    return normal;
}


float Terrain::getHeight(int x, int z, float ** map, int size){
    if(x < 0 || z < 0 || x >= size || z >= size)
        return 0;
    float height = map[x][z] * MAX_HEIGHT;
    return height;
}

PointerRawModel Terrain::generateTerrain(Loader loader, float ** map, GLuint size){
    GLuint VERTEX_COUNT = size;

    int count = VERTEX_COUNT * VERTEX_COUNT;
//    float * vertices = new float[count * 3];
//    float * normals = new float[count * 3];
//    float * textures = new float[count * 2];
    int number = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);
//    GLuint * indices = new GLuint[number];
    std::vector<float> vertices, normals, textures;
    std::vector<GLuint> indices;
    int vertexPointer = 0;
    for(int i=0 ; i<VERTEX_COUNT ; i++){
        for(int j=0 ; j<VERTEX_COUNT ; j++){
            vertices.push_back((float)j / ((float)VERTEX_COUNT - 1) * SIZE);
            vertices.push_back(getHeight(j, i, map, size));
            vertices.push_back((float)i / ((float)VERTEX_COUNT - 1) * SIZE);
            Vector3f normal = calculateNormal(j, i, map, size);
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
            textures.push_back((float)j / ((float)VERTEX_COUNT - 1));
            textures.push_back((float)i / ((float)VERTEX_COUNT - 1));
            vertexPointer++;
        }
    }
    int pointer = 0;
    for(int gz=0 ; gz<VERTEX_COUNT-1 ; gz++){
        for(int gx=0 ; gx<VERTEX_COUNT-1 ; gx++){
            GLuint topLeft = gz * VERTEX_COUNT + gx;
            GLuint topRight = topLeft + 1;
            GLuint bottomLeft = (gz + 1) * VERTEX_COUNT + gx;
            GLuint bottomRight = bottomLeft + 1;
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
    printf("v: %zu, t: %zu, n: %zu, i: %zu\n", vertices.size(), textures.size(), normals.size(), indices.size());
    PointerRawModel result = loader.loadToVao(vertices, textures, normals, indices);
    for(int i=0 ; i<size ; i++)
        delete[] map[i];

    delete[] map;
    return result;
}
float** Terrain::create(GLuint x2, GLuint y2){
    float ** map = new float * [x2];
    for(int i=0 ; i<x2 ; i++)
        map[i] = new float[y2];

    map[0][0] 		    = static_cast<float>(rand() / RAND_MAX);
    map[0][y2 - 1]      = static_cast<float>(rand() / RAND_MAX);
    map[x2 - 1][0]      = static_cast<float>(rand() / RAND_MAX);
    map[x2 - 1][y2 - 1] = static_cast<float>(rand() / RAND_MAX);

    generateMap(0, 0, x2 - 1, y2 - 1, map);

//    for(int i=0 ; i<x2 ; i++){
//        for(int j=0 ; j<y2 ; j++)
//            printf("[%d][%d]%f ",i,j, map[i][j]);
//        printf("\n");
//    }

    return map;
}

void Terrain::generateMap(int x1, int y1, int x2, int y2, float ** map) {
    float cl1 = map[x1][y1];
    float cl2 = map[x2][y1];
    float cl3 = map[x1][y2];
    float cl4 = map[x2][y2];

    Vector2f b1 = Vector2f((x1 + x2) / 2, y1);
    map[b1.getXi()][b1.getYi()] =  (cl1 + cl2) / 2;

    Vector2f b2 = Vector2f((x1 + x2) / 2, y2);
    map[b2.getXi()][b2.getYi()] =  (cl3 + cl4) / 2;

    Vector2f b3 = Vector2f(x1, (y1 + y2) / 2);
    map[b3.getXi()][b3.getYi()] =  (cl1 + cl3) / 2;

    Vector2f b4 = Vector2f(x2, (y1 + y2) / 2);
    map[b4.getXi()][b4.getYi()] =  (cl2 + cl4) / 2;

    Vector2f b5 = Vector2f((x1 + x2) / 2, (y1 + y2) / 2);
    map[b5.getXi()][b5.getYi()] =  (cl1 + cl2 + cl3 + cl4) / 4 + static_cast<float>(rand() / (RAND_MAX) + 1);

    if(x2 - x1 <= 2 || y2 - y1 <= 2)
        return;

    generateMap(x1, y1, b5.getXi(), b5.getYi(), map);
    generateMap(b1.getXi(), b1.getYi(), b4.getXi(), b4.getYi(), map);
    generateMap(b3.getXi(), b3.getYi(), b2.getXi(), b2.getYi(), map);
    generateMap(b5.getXi(), b5.getYi(), x2, y2, map);
}