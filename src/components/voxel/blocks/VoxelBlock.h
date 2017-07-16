//
// Created by gabriel on 13.5.2017.
//

#ifndef GAMEENGINE_VOXELBLOCK_H
#define GAMEENGINE_VOXELBLOCK_H

#include <src/components/voxel/blocks/BlockDatabase.h>
class VoxelBlock{
    const uint8_t _type = static_cast<uint8_t>(BlockID::Air);
public:
    inline VoxelBlock(void) = default;
    inline VoxelBlock(uint8_t type) : _type(type){};
    inline VoxelBlock(BlockID type) : _type(static_cast<uint8_t>(type)){};

    inline const BlockType& getType(void) const{
        return BlockDatabase::get().get(_type);
    }
    inline const BlockData& getData(void) const{
        return BlockDatabase::get().get(_type).getData();
    }
};

#endif //GAMEENGINE_VOXELBLOCK_H
