//
// Created by gabriel on 21.5.2017.
//

#ifndef GAMEENGINE_CHUNKGENERATOR_H
#define GAMEENGINE_CHUNKGENERATOR_H

#include <src/components/terrain/HeightGenerator.h>
#include <src/components/voxel/blocks/BlockID.h>

class ChunkGenerator{
    const HeightGenerator _generator;
    uint getHeight(int x, int z) const{
        return (uint)((_generator.generateHeight(x, z) + 1) * (CHUNK_SIZE * NUMBER_OF_MINICHUNKS)) >> 1;
    }
public:
    inline ChunkGenerator(float amplitude, int seed) :
            _generator(HeightGenerator(amplitude, seed)){
    };
    BlockID getBlockType2(int x, uint y, int z) const{
        return y < getHeight(x, z) ? BlockID::Grass : BlockID::Air;
    }
    LightBlockData getBlockType(int x, uint y, int z) const{
        LightBlockData data;
        data.type = y < getHeight(x, z) ? BlockID::Grass : BlockID::Air;
        return data;
    }
    inline LightBlockData*** generateMap(Vector3f chunkSize, int offsetX, uint offsetY, int offsetZ) const{
        LightBlockData *** map = new LightBlockData ** [chunkSize.getXi()];
        for (uint i = 0; i < chunkSize.x; i++) {
            map[i] = new LightBlockData * [chunkSize.getYi()];
            for (uint j = 0; j < chunkSize.y; j++) {
                map[i][j] = new LightBlockData[chunkSize.getZi()];
                for (uint k = 0; k < chunkSize.z; k++) {
                    map[i][j][k] = LightBlockData((float)i, (float)j, (float)k);
                }
            }
        }
        for (uint i = 0; i < chunkSize.x; i++) {
            for (uint k = 0; k < chunkSize.z; k++) {
                int height = getHeight(offsetX + i, offsetZ + k) - offsetY;
//                int height = (uint)((_generator.generateHeight(offsetX + i, offsetZ + k) + 1) * (CHUNK_SIZE * NUMBER_OF_MINICHUNKS) / 2) - offsetY;
                if(height <= 0){
                    continue;
                }
                if(height > chunkSize.getYi()){
                    height = chunkSize.getYi();
                }
                for (int j = 0 ; j < height ; j++) {
                    map[i][j][k].type = BlockID::Dirt;
                }
            }
        }
        return map;
    }
    inline BlockID*** generateMap2(Vector3f chunkSize, int offsetX, uint offsetY, int offsetZ) const{
        BlockID *** map = new BlockID ** [chunkSize.getXi()];
        for (uint i = 0; i < chunkSize.x; i++) {
            map[i] = new BlockID * [chunkSize.getYi()];
            for (uint j = 0; j < chunkSize.y; j++) {
                map[i][j] = new BlockID [chunkSize.getZi()];
                for (uint k = 0; k < chunkSize.z; k++) {
                    map[i][j][k] = BlockID::Air;
                }
            }
        }
        for (uint i = 0; i < chunkSize.x; i++) {
            for (uint k = 0; k < chunkSize.z; k++) {
                int height = getHeight(offsetX + i, offsetZ + k) - offsetY;
//                int height = (uint)((_generator.generateHeight(offsetX + i, offsetZ + k) + 1) * (CHUNK_SIZE * NUMBER_OF_MINICHUNKS) / 2) - offsetY;
                if(height <= 0){
                    continue;
                }
                if(height > chunkSize.getYi()){
                    height = chunkSize.getYi();
                }
                for (int j = 0 ; j < height ; j++) {
                    map[i][j][k] = BlockID::Dirt;
                }
            }
        }
        return map;
    }
    inline void clearMap(LightBlockData *** map, Vector3f chunkSize) const{
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
    inline void clearMap2(BlockID *** map, Vector3f chunkSize) const{
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

};

#endif //GAMEENGINE_CHUNKGENERATOR_H
