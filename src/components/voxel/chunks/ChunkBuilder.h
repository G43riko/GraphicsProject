//
// Created by gabriel on 13.5.2017.
//

#ifndef GAMEENGINE_CHUNKBUILDER_H
#define GAMEENGINE_CHUNKBUILDER_H


#include <src/utils/math/objects/Vectors.h>
#include <src/rendering/model/Mesh.h>

struct LightBlockData{
    float x, y, z;
    float w = BLOCK_SIZE, h = BLOCK_SIZE, d = BLOCK_SIZE;
    BlockID type = BlockID ::Air;

    LightBlockData * parent = this;

    LightBlockData(float x = 0, float y = 0, float z = 0, BlockID type = BlockID::Air) :
            x(x),
            y(y),
            z(z),
            type(type){}
    inline bool operator==(const LightBlockData& rhs){
        return EQ(x, rhs.x) && EQ(y, rhs.y) && EQ(z, rhs.z);
    }
    inline bool operator!=( const LightBlockData& rhs){ return !(*this == rhs); }
};

#include "ChunkGenerator.h"

struct Vert{
    Vector3f pos;
    Vector2f tex;
    uint indice;
};

class ChunkBuilder{
    const std::vector<uint> clockWiseIndices = {3, 1, 0, 2, 1, 3};
    const std::vector<uint> antiClockWiseIndices = {0, 1, 3, 3, 1, 2};
    const ChunkGenerator generator = ChunkGenerator(1.0f, 1);
    const float _size;
    VectorV3 positions;
    VectorV2 textures;
    VectorV3 normals;
    VectorUI indices;
    std::map<std::string, uint> data;
    std::map<std::string, Vert> vertices;
    uint maxIndice = 0;
    const float w = _size, h = _size, d = _size;
    const Vector3f _chunkSize;
    inline void generateFront(Vector3f position){
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
    inline void generateBack(Vector3f position){
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
    inline void generateRight(Vector3f position){
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
    inline void generateLeft(Vector3f position){
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
    inline void generateBottom(Vector3f position){
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
    inline void generateUp(Vector3f position){
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

    inline void generateUp2(Vector3f position){
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

    inline void generate(const VectorV3& pos, const VectorV2& texts, const Vector3f& normal, bool clockWise){
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

    inline static bool isOpaque2(BlockID block){
        //TODO toto zistovať v BlockDatabase podla blockTypu
        return block == BlockID ::Air;
    }
    inline static bool isOpaque(LightBlockData block){
        //TODO toto zistovať v BlockDatabase podla blockTypu
        return block.type == BlockID ::Air;
    }

public:
    inline ChunkBuilder(const Vector3f& chunkSize, float size) :
            _size(size / 2),
            _chunkSize(chunkSize){}

    inline void generate(Vector3f position = Vector3f()){
        //BlockID *** map = generator.generateMap(_chunkSize, position.getXi(), position.getYi(), position.getZi());
        LightBlockData *** map = generator.generateMap(_chunkSize, position.getXi(), position.getYi(), position.getZi());

//        simplifyMap(map);

        generateFromMap(map, position);

        generator.clearMap(map, _chunkSize);
    }

    void simplifyMap(LightBlockData *** & map){
        //X - axis
        for(int i=1 ; i<_chunkSize.x ; i++){
            for(int j=0 ; j<_chunkSize.y ; j++){
                for(int k=0 ; k<_chunkSize.z ; k++){
                    LightBlockData * actBlock = &map[i][j][k];
                    LightBlockData * cmpBlock = &map[i - 1][j][k];
                    if(isOpaque(*actBlock) || *actBlock -> parent != map[i][j][k]){
                        continue;
                    }
                    if(!isOpaque(*cmpBlock) &&
                       cmpBlock -> parent -> type == actBlock -> type &&
                       EQ(cmpBlock -> parent -> h, actBlock -> h) &&
                       EQ(cmpBlock -> parent -> w, actBlock -> w) &&
                       EQ(cmpBlock -> parent -> y, actBlock -> y) &&
                       EQ(cmpBlock -> parent -> z, actBlock -> z)){
                        actBlock -> parent = map[i - 1][j][k].parent;
                        actBlock -> parent -> w += actBlock -> w;
                    }
                }
            }
        }
    }

    inline void generateFromMap(LightBlockData *** map, Vector3f position){
        LOOP(_chunkSize.x, i){
            LOOP(_chunkSize.y, j){
                LOOP(_chunkSize.z, k){
                    if(isOpaque(map[i][j][k]) /*|| map[i][j][k].parent != &map[i][j][k]*/){
                        continue;
                    }
                    Vector3f pos = position + Vector3f(i, j, k);

                    if(i == 0 || (i > 0 && isOpaque(map[i - 1][j][k]))){
                        generateLeft(pos);
                    }
                    if(i == _chunkSize.getXi() - 1 || (i < _chunkSize.x - 1 && isOpaque(map[i + 1][j][k]))){
                        generateRight(pos);
                    }

                    if(j == 0 || (j > 0 && isOpaque(map[i][j - 1][k]))){
                        if(false && j == 0 && position.y  > 0 && !isOpaque(generator.getBlockType(i, position.y - 1, k))){
//                            printf("dole\n");
                        }
                        else{
                            generateBottom(pos);
                        }
                    }
                    if(j == _chunkSize.getYi() - 1 || (j < _chunkSize.y - 1 && isOpaque(map[i][j + 1][k]))){
                        if(false && j == _chunkSize.getYi() - 1  && !isOpaque(generator.getBlockType(i, pos.y + 1, j))){
//                            printf("hore\n");
                        }
                        else{
                            generateUp(pos);
                        }
                    }

                    if(k == 0 || (k > 0 && isOpaque(map[i][j][k - 1]))){
                        generateFront(pos);
                    }
                    if(k == _chunkSize.getZi() - 1 || (k < _chunkSize.z - 1 && isOpaque(map[i][j][k + 1]))){
                        generateBack(pos);
                    }
                }
            }
        }
    }

    PointerMesh getMesh(void){
        VectorF finalPositions;
        VectorF finalNormals;
        VectorF finalTangents;
        VectorF finalTextures;

        finalPositions.reserve(indices.size() * 3);
        finalTextures.reserve(indices.size() * 2);
        finalNormals.reserve(indices.size() * 3);

        ITERATE_VECTOR(indices, i){
            finalPositions.push_back(positions[i].x);
            finalPositions.push_back(positions[i].y);
            finalPositions.push_back(positions[i].z);

            finalTextures.push_back(textures[i].x);
            finalTextures.push_back(textures[i].y);

            finalNormals.push_back(normals[i].x);
            finalNormals.push_back(normals[i].y);
            finalNormals.push_back(normals[i].z);
        }

        return Mesh::create(finalPositions, finalTextures, finalNormals, finalTangents, indices);
    }
};

#endif //GAMEENGINE_CHUNKBUILDER_H
