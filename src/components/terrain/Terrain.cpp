//
// Created by gabriel on 12.11.2016.
//

#include "Terrain.h"

Vector3f Terrain::calculateNormal(int x, int z, float ** map, int size){
    float heightL = getHeight(x - 1, z, map, size);
    float heightR = getHeight(x + 1, z, map, size);
    float heightD = getHeight(x, z - 1, map, size);
    float heightU = getHeight(x, z + 1, map, size);
    return Vector3f(heightL - heightR, 2.0f, heightD - heightU).normalize();
}


float Terrain::getHeight(int x, int z, float ** map, int size){
    if(x < 0 || z < 0 || x >= size || z >= size)
        return 0;
    float height = map[x][z];
    return height;
}

PointerRawModel Terrain::generateTerrain(Loader loader, float ** map, GLuint size, int vertexCount, int textMulti){
    std::vector<float> vertices, normals, textures;
    std::vector<GLuint> indices;
    for(unsigned int i=0 ; i<vertexCount ; i++){
        for(unsigned int j=0 ; j<vertexCount ; j++){
            map[j][i] = generator.generateHeight(j, i);

            vertices.push_back((float)j / (vertexCount - 1) * size);
            vertices.push_back(map[j][i]);
            vertices.push_back((float)i / (vertexCount - 1) * size);

            textures.push_back((float)j / (vertexCount - 1) * textMulti);
            textures.push_back((float)i / (vertexCount - 1) * textMulti);
        }
    }
    for(unsigned int gz=0 ; gz<vertexCount ; gz++){
        for(unsigned int gx=0 ; gx<vertexCount ; gx++){
            Vector3f normal = calculateNormal(gx, gz, map, vertexCount);
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
            if(gz < vertexCount - 1 && gx < vertexCount - 1){
                GLuint topLeft = gz * vertexCount + gx;
                GLuint topRight = topLeft + 1;
                GLuint bottomLeft = (gz + 1) * vertexCount + gx;
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
    return loader.loadToVao(vertices, textures, normals, indices);
}