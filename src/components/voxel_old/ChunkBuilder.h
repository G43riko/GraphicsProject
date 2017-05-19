//
// Created by gabriel on 13.5.2017.
//

#ifndef GAMEENGINE_CHUNKBUILDER_H
#define GAMEENGINE_CHUNKBUILDER_H


#include <src/utils/math/objects/Vectors.h>
#include <src/rendering/model/Mesh.h>

struct Vert{
    Vector3f pos;
    Vector2f tex;
    uint indice;
};

class ChunkBuilder{
    const std::vector<uint> clockWiseIndices = {3, 1, 0, 2, 1, 3};
    const std::vector<uint> antiClockWiseIndices = {0, 1, 3, 3, 1, 2};
    float _size;
    VectorV3 positions;
    VectorV2 textures;
    VectorV3 normals;
    std::map<std::string, uint> data;
    std::map<std::string, Vert> vertices;
    uint maxIndice = 0;
    float   w = _size,
            h = _size,
            d = _size;
    VectorUI indices;
    inline std::string toString(float x, float y, float z){
        return std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
    }
    void generateFront(Vector3f position){
        generate({{position.x + -w, position.y +  h, position.z + -d},
                  {position.x + -w, position.y + -h, position.z + -d},
                  {position.x +  w, position.y + -h, position.z + -d},
                  {position.x +  w, position.y +  h, position.z + -d}},
                 {{0, 0},
                  {0, 1},
                  {1, 1},
                  {1, 0}},
                 {0, 0, -1}, true);
        return;
        positions.push_back({position.x + -w, position.y +  h, position.z + -d});
        positions.push_back({position.x + -w, position.y + -h, position.z + -d});
        positions.push_back({position.x +  w, position.y + -h, position.z + -d});
        positions.push_back({position.x +  w, position.y +  h, position.z + -d});

        textures.push_back({0, 0});
        textures.push_back({0, 1});
        textures.push_back({1, 1});
        textures.push_back({1, 0});

        normals.push_back({0, 0, -1});
        normals.push_back({0, 0, -1});
        normals.push_back({0, 0, -1});
        normals.push_back({0, 0, -1});

        indices.push_back(maxIndice + 3);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 0);

        indices.push_back(maxIndice + 2);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 3);
        maxIndice += 4;
    };
    void generateBack(Vector3f position){
        positions.push_back({position.x + -w, position.y +  h, position.z + d});
        positions.push_back({position.x + -w, position.y + -h, position.z + d});
        positions.push_back({position.x +  w, position.y + -h, position.z + d});
        positions.push_back({position.x +  w, position.y +  h, position.z + d});

        textures.push_back({0, 0});
        textures.push_back({0, 1});
        textures.push_back({1, 1});
        textures.push_back({1, 0});

        normals.push_back({0, 0, 1});
        normals.push_back({0, 0, 1});
        normals.push_back({0, 0, 1});
        normals.push_back({0, 0, 1});

        indices.push_back(maxIndice + 0);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 3);

        indices.push_back(maxIndice + 3);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 2);
        maxIndice += 4;
    };
    void generateRight(Vector3f position){
        generate({{position.x + w, position.y +  h, position.z + -d},
                  {position.x + w, position.y + -h, position.z + -d},
                  {position.x + w, position.y + -h, position.z +  d},
                  {position.x + w, position.y +  h, position.z +  d}},
                 {{0, 0},
                  {0, 1},
                  {1, 1},
                  {1, 0}},
                 {1, 0, 0}, true);
        return;
        positions.push_back({position.x + w, position.y +  h, position.z + -d});
        positions.push_back({position.x + w, position.y + -h, position.z + -d});
        positions.push_back({position.x + w, position.y + -h, position.z +  d});
        positions.push_back({position.x + w, position.y +  h, position.z +  d});

        textures.push_back({0, 0});
        textures.push_back({0, 1});
        textures.push_back({1, 1});
        textures.push_back({1, 0});

        normals.push_back({1, 0, 0});
        normals.push_back({1, 0, 0});
        normals.push_back({1, 0, 0});
        normals.push_back({1, 0, 0});

        indices.push_back(maxIndice + 3);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 0);

        indices.push_back(maxIndice + 2);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 3);
        maxIndice += 4;
    };
    void generateLeft(Vector3f position){
        positions.push_back({position.x + -w, position.y +  h, position.z + -d});
        positions.push_back({position.x + -w, position.y + -h, position.z + -d});
        positions.push_back({position.x + -w, position.y + -h, position.z +  d});
        positions.push_back({position.x + -w, position.y +  h, position.z +  d});

        textures.push_back({0, 0});
        textures.push_back({0, 1});
        textures.push_back({1, 1});
        textures.push_back({1, 0});

        normals.push_back({-1, 0, 0});
        normals.push_back({-1, 0, 0});
        normals.push_back({-1, 0, 0});
        normals.push_back({-1, 0, 0});

        indices.push_back(maxIndice + 0);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 3);

        indices.push_back(maxIndice + 3);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 2);
        maxIndice += 4;
    };
    void generateBottom(Vector3f position){
        positions.push_back({position.x + -w, position.y + -h, position.z +  d});
        positions.push_back({position.x + -w, position.y + -h, position.z + -d});
        positions.push_back({position.x +  w, position.y + -h, position.z + -d});
        positions.push_back({position.x +  w, position.y + -h, position.z +  d});

        textures.push_back({0, 0});
        textures.push_back({0, 1});
        textures.push_back({1, 1});
        textures.push_back({1, 0});

        normals.push_back({0, -1, 0});
        normals.push_back({0, -1, 0});
        normals.push_back({0, -1, 0});
        normals.push_back({0, -1, 0});

        indices.push_back(maxIndice + 0);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 3);

        indices.push_back(maxIndice + 3);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 2);
        maxIndice += 4;
    };
    void generateUp(Vector3f position){
        generate({{position.x + -w, position.y + h, position.z +  d},
                  {position.x + -w, position.y + h, position.z + -d},
                  {position.x +  w, position.y + h, position.z + -d},
                  {position.x +  w, position.y + h, position.z +  d}},
                 {{0, 0},
                  {0, 1},
                  {1, 1},
                  {1, 0}},
                 {0, 1, 0}, true);
        return;
        positions.push_back({position.x + -w, position.y + h, position.z +  d});
        positions.push_back({position.x + -w, position.y + h, position.z + -d});
        positions.push_back({position.x +  w, position.y + h, position.z + -d});
        positions.push_back({position.x +  w, position.y + h, position.z +  d});

        textures.push_back({0, 0});
        textures.push_back({0, 1});
        textures.push_back({1, 1});
        textures.push_back({1, 0});

        normals.push_back({0, 1, 0});
        normals.push_back({0, 1, 0});
        normals.push_back({0, 1, 0});
        normals.push_back({0, 1, 0});

        indices.push_back(maxIndice + 3);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 0);

        indices.push_back(maxIndice + 2);
        indices.push_back(maxIndice + 1);
        indices.push_back(maxIndice + 3);
        printf("aaaa\n");
        maxIndice += 4;
    };

    void generateUp2(Vector3f position){
        Vector3f v0 = {position.x + -w, position.y + h, position.z +  d};
        Vector3f v1 = {position.x + -w, position.y + h, position.z + -d};
        Vector3f v2 = {position.x +  w, position.y + h, position.z + -d};
        Vector3f v3 = {position.x +  w, position.y + h, position.z +  d};
        uint indiceIncrease = 0;
        uint ind0, ind1, ind2, ind3;

        if(data.find(v0.toString()) == data.end()){
            positions.push_back(v0);//0
            textures.push_back({0, 0});
            normals.push_back({0, 1, 0});
            ind0 = data[v0.toString()] = maxIndice + indiceIncrease++;
        }
        else{
            ind0 = data[v0.toString()];
        }

        if(data.find(v1.toString()) == data.end()){
            positions.push_back(v1);//1
            textures.push_back({0, 1});
            normals.push_back({0, 1, 0});
            ind1 = data[v1.toString()] = maxIndice + indiceIncrease++;
        }
        else{
            ind1 = data[v1.toString()];
        }

        if(data.find(v2.toString()) == data.end()){
            positions.push_back(v2);//2
            textures.push_back({1, 1});
            normals.push_back({0, 1, 0});
            ind2 = data[v2.toString()] = maxIndice + indiceIncrease++;
        }
        else{
            ind2 = data[v2.toString()];
        }

        if(data.find(v3.toString()) == data.end()){
            positions.push_back(v3);//3
            textures.push_back({1, 0});
            normals.push_back({0, 1, 0});
            ind3 = data[v3.toString()] = maxIndice + indiceIncrease++;
        }
        else{
            ind3 = data[v3.toString()];
        }

        indices.push_back(ind3);
        indices.push_back(ind1);
        indices.push_back(ind0);

        indices.push_back(ind2);
        indices.push_back(ind1);
        indices.push_back(ind3);
        maxIndice += indiceIncrease;
    };

    void generate(VectorV3 pos, VectorV2 texts, Vector3f normal, bool clockWise){
        positions.push_back(pos[0]);
        positions.push_back(pos[1]);
        positions.push_back(pos[2]);
        positions.push_back(pos[3]);
//        positions.insert(positions.end(), {pos[0], pos[1], pos[2], pos[3]});
        textures.push_back(texts[0]);
        textures.push_back(texts[1]);
        textures.push_back(texts[2]);
        textures.push_back(texts[3]);
//        textures.insert(textures.end(), {texts[0], texts[1], texts[2], texts[3]});
        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
//        normals.insert(normals.end(), {normal, normal, normal, normal});

        if(clockWise){
            indices.push_back(maxIndice + clockWiseIndices[0]);
            indices.push_back(maxIndice + clockWiseIndices[1]);
            indices.push_back(maxIndice + clockWiseIndices[2]);
            indices.push_back(maxIndice + clockWiseIndices[3]);
            indices.push_back(maxIndice + clockWiseIndices[4]);
            indices.push_back(maxIndice + clockWiseIndices[5]);
//            indices.insert(indices.end(), {maxIndice + clockWiseIndices[0],
//                                           maxIndice + clockWiseIndices[1],
//                                           maxIndice + clockWiseIndices[2],
//                                           maxIndice + clockWiseIndices[3],
//                                           maxIndice + clockWiseIndices[4],
//                                           maxIndice + clockWiseIndices[5]});
        }
        else{
            indices.push_back(maxIndice + antiClockWiseIndices[0]);
            indices.push_back(maxIndice + antiClockWiseIndices[1]);
            indices.push_back(maxIndice + antiClockWiseIndices[2]);
            indices.push_back(maxIndice + antiClockWiseIndices[3]);
            indices.push_back(maxIndice + antiClockWiseIndices[4]);
            indices.push_back(maxIndice + antiClockWiseIndices[5]);
//            indices.insert(indices.end(), {maxIndice + antiClockWiseIndices[0],
//                                           maxIndice + antiClockWiseIndices[1],
//                                           maxIndice + antiClockWiseIndices[2],
//                                           maxIndice + antiClockWiseIndices[3],
//                                           maxIndice + antiClockWiseIndices[4],
//                                           maxIndice + antiClockWiseIndices[5]});
        }

        maxIndice += 4;
    }
public:
    ChunkBuilder(float size) : _size(size){
        generateFromMap(nullptr, {16, 256, 16}, {0, 0, 0});
    }
    ChunkBuilder(Vector3f chunkSize, float size, Vector3f position = Vector3f()) : _size(size) {
        int *** map = new int ** [chunkSize.getXi()];
        for (int i = 0; i < chunkSize.x; i++) {
            map[i] = new int * [chunkSize.getYi()];
            for (int j = 0; j < chunkSize.y; j++) {
                map[i][j] = new int [chunkSize.getZi()];
                for (int k = 0; k < chunkSize.z; k++) {
                    map[i][j][k] = RANDOMI(-1, 2);
                }
            }
        }

        generateFromMap(map, chunkSize, position);

        for (int i = 0; i < chunkSize.x; i++) {
            for (int j = 0; j < chunkSize.y; j++) {
                for (int k = 0; k < chunkSize.z; k++) {
                }
                delete[] map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;

    }

    void generateFromMap(int *** map, Vector3f size, Vector3f position){
        for(int i=0 ; i<size.x ; i++){
            for(int j=0 ; j<size.y ; j++){
                for(int k=0 ; k<size.z ; k++){
                    if(map[i][j][k] <= 0){
                        continue;
                    }
                    Vector3f pos = position + Vector3f(i * 2, j * 2, k * 2);

                    if(i == 0 || (i > 0 && map[i - 1][j][k] <= 0)){
                        generateLeft(pos);
                    }
                    if(i == size.getXi() - 1 || (i < size.x - 1 && map[i + 1][j][k] <= 0)){
                        generateRight(pos);
                    }

                    if(j == 0 || (j > 0 && map[i][j - 1][k] <= 0)){
                        generateBottom(pos);
                    }
                    if(j == size.getYi() - 1 || (j < size.y - 1 && map[i][j + 1][k] <= 0)){
                        generateUp(pos);
                    }

                    if(k == 0 || (k > 0 && map[i][j][k - 1] <= 0)){
                        generateFront(pos);
                    }
                    if(k == size.getZi() - 1 || (k < size.z - 1 && map[i][j][k + 1] <= 0)){
                        generateBack(pos);
                    }
                }
            }
        }
    }

    void generateBlock(Vector3f pos){
        generateUp(pos);
        generateBottom(pos);
        generateLeft(pos);
        generateRight(pos);
        generateFront(pos);
        generateBack(pos);
    }

    PointerMesh getMesh(void){
        VectorF finalPositions;
        VectorF finalNormals;
        VectorF finalTangents;
        VectorF finalTextures;
//        std::map<std::string, int> data;
//        int counter = 0;
        for(auto position : positions){
//            if(data.find(position.toString()) == data.end()){
//                data[position.toString()] = 0;
//            }
//            else{
//                data[position.toString()]++;
//                counter++;
//            }
            finalPositions.push_back(position.x);
            finalPositions.push_back(position.y);
            finalPositions.push_back(position.z);
        }
        printf("text:");
        for(auto texture : textures){
            finalTextures.push_back(texture.x);
            finalTextures.push_back(texture.y);
        }
        printf("norm:");
        for(auto normal : normals){
            finalNormals.push_back(normal.x);
            finalNormals.push_back(normal.y);
            finalNormals.push_back(normal.z);
        }
        //      50686
        //pos: 202752, texts: 135168, indices: 101376 -> 16 * 256 * 16;
//        printf("pos: %lu, texts: %lu, indices: %lu, opakujucich: %d\n", finalPositions.size(), finalTextures.size(), indices.size(), counter);
        return Mesh::create(finalPositions, finalTextures, finalNormals, finalTangents, indices);
    }
};

#endif //GAMEENGINE_CHUNKBUILDER_H

/*
 const float w = 0.5;
const float h = 0.5;
const float d = 0.5;

PointerMesh cube = PointerMesh(new Mesh({-w, h,-d,//BACK
                                         -w,-h,-d,
                                          w,-h,-d,
                                          w, h,-d,

                                         -w, h, d,//FORWARD
                                         -w,-h, d,
                                          w,-h, d,
                                          w, h, d,

                                          w, h,-d,//RIGHT
                                          w,-h,-d,
                                          w,-h, d,
                                          w, h, d,

                                         -w, h,-d,//LEFT
                                         -w,-h,-d,
                                         -w,-h, d,
                                         -w, h, d,

                                         -w, h, d,//UP
                                         -w, h,-d,
                                          w, h,-d,
                                          w, h, d,

                                         -w,-h, d,//BOTTOM
                                         -w,-h,-d,
                                          w,-h,-d,
                                          w,-h, d},
                                        { 0,0,0,1,1,1,1,0,
                                          0,0,0,1,1,1,1,0,
                                          0,0,0,1,1,1,1,0,
                                          0,0,0,1,1,1,1,0,
                                          0,0,0,1,1,1,1,0,
                                          0,0,0,1,1,1,1,0},
                                        {  0,  1,  3,  3,  1,  2,
                                           4,  5,  7,  7,  5,  6,
                                           8,  9, 11, 11,  9, 10,
                                          12, 13, 15, 15, 13, 14,
                                          16, 17, 19, 19, 17, 18,
                                          20, 21, 23, 23, 21, 22}));
 */