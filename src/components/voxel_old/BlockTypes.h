//
// Created by gabriel on 7.5.2017.
//

#ifndef GAMEENGINE_BLOCKTYPES_H
#define GAMEENGINE_BLOCKTYPES_H

#include <memory>
#include <vector>
#include <src/utils/GTypes.h>
#include <src/utils/GUtils.h>

enum class BlockIDs{
    GRASS,
    SAND,
    DIRT,
    WATER,
    DIAMOND,
    NUM_BLOCK_TYPES
};

//inline static Vector4f getColorByType(BlockType type){
//        switch (type){
//            -case BlockType::yellow: return Vector4f(1, 1, 0, 1);
//            case BlockType::aqua: return Vector4f(0, 1, 1, 1);
//            case BlockType::magenta: return Vector4f(1, 0, 1, 1);
//            -case BlockType::red: return Vector4f(1, 0, 0, 1);
//            -case BlockType::green: return Vector4f(0, 1, 0, 1);
//            case BlockType::blue: return Vector4f(0, 0, 1, 1);
//            case BlockType::black: return Vector4f(0, 0, 0, 1);
//            default: return Vector4f(1, 1, 1, 1);
//        }
//    }
class BlockTypes{
private:
    std::vector<MaterialData> blocks = std::vector<MaterialData>((int)BlockIDs::NUM_BLOCK_TYPES);
public:
    BlockTypes(void){
        blocks[(int)BlockIDs::GRASS]    = {{0.0f, 1.0f, 0.0f}, {0.0f, 0.1f, 0.0f}, {1.0f, 0.0f, 0.0f}, 0.5f, 50.0f}; //GREEN
        blocks[(int)BlockIDs::DIRT]     = {{1.0f, 0.0f, 0.0f}, {0.1f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0.5f, 100.0f}; //RED
        blocks[(int)BlockIDs::SAND]     = {{1.0f, 1.0f, 0.0f}, {0.1f, 0.1f, 0.0f}, {1.0f, 0.0f, 0.0f}, 0.5f, 500.0f}; //YELLOW
        blocks[(int)BlockIDs::WATER]    = {{0.0f, 1.0f, 1.0f}, {0.0f, 0.1f, 0.1f}, {1.0f, 0.0f, 0.0f}, 1.0f, 1000.0f}; //AQUA
        blocks[(int)BlockIDs::DIAMOND]  = {{1.0f, 0.0f, 1.0f}, {0.1f, 0.0f, 0.1f}, {1.0f, 0.0f, 0.0f}, 1.0f, 2000.0f}; //MAGENTA
    }
    inline MaterialData get(uint8_t id) const{
        return blocks[id];
    }
    inline MaterialData get(BlockIDs blockID) const{
        return blocks[(int)blockID];
    }
    inline static BlockIDs getRandomType(void){
        return static_cast<BlockIDs>(rand() % (int)BlockIDs::NUM_BLOCK_TYPES);
    }

    inline static MaterialData getMaterialOf(BlockIDs id){
        static BlockTypes blockTypes;
        return blockTypes.get(id);
    }
};

#endif //GAMEENGINE_BLOCKTYPES_H
