//
// Created by gabriel on 12.11.2016.
//

#include "Terrain.h"

Vector3f Terrain::calculateNormal(int x, int z){
    float heightL = getTerrainHeight(x - 1, z);
    float heightR = getTerrainHeight(x + 1, z);
    float heightD = getTerrainHeight(x, z - 1);
    float heightU = getTerrainHeight(x, z + 1);
    return Vector3f(heightL - heightR, 2.0f, heightD - heightU).normalize();
}

float Terrain::getTerrainHeight(int x, int z){
    if(x < 0 || z < 0 || x >= vertices || z >= vertices)
        return 0;
    float height = map[x][z];
    return height;
}

PointerRawModel Terrain::generateTerrain(Loader loader, int textMulti){
    std::vector<float> verticesVector, normals, textures;
    std::vector<GLuint> indices;

    //vygeneruje výškovú mapu pre terén a vypočíta súradnice pre textúru
    for(unsigned int i=0 ; i<vertices ; i++){
        for(unsigned int j=0 ; j<vertices ; j++){
            map[j][i] = generator.generateHeight(j, i);

            verticesVector.push_back((float)j / (vertices - 1) * size);
            verticesVector.push_back(map[j][i]);
            verticesVector.push_back((float)i / (vertices - 1) * size);

            textures.push_back((float)j / (vertices - 1) * textMulti);
            textures.push_back((float)i / (vertices - 1) * textMulti);
        }
    }
    PRINT(map[0][0] << ", " << map[10][0] << ", " << map[0][10] << ", " << map[10][10]);
    PRINT(map[0][0] << ", " << map[20][0] << ", " << map[0][20] << ", " << map[20][20]);
    PRINT(map[0][0] << ", " << map[30][0] << ", " << map[0][30] << ", " << map[30][30]);

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
    return loader.loadToVao(verticesVector, textures, normals, indices);
}