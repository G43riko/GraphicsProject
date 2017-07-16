//
// Created by gabriel on 16.7.2017.
//

#ifndef GAMEENGINE_CHUNKSECTION_H
#define GAMEENGINE_CHUNKSECTION_H

#include <src/components/voxel/blocks/VoxelBlock.h>
#include <src/components/voxel_old/WoldConst.h>

class ChunkSection{
    std::array<VoxelBlock, CHUNK_VOLUME> _blocks;
    Vector3f _position;

    inline static uint index(uint x, uint y, uint z){
        return y * CHUNK_AREA + z * CHUNK_SIZE + x;
    }
public:
    const VoxelBlock& getBlock(uint x, uint y, uint z) const{
        if(x > BLOCK_SIZE){return BlockID::Air; }
        if(y > BLOCK_SIZE){return BlockID::Air; }
        if(z > BLOCK_SIZE){return BlockID::Air; }

        return _blocks[index(x, y, z)];
    }

    inline void setBlock(uint x, uint y, uint z, VoxelBlock block){
        if(x > BLOCK_SIZE){return; }
        if(y > BLOCK_SIZE){return; }
        if(z > BLOCK_SIZE){return; }

        _blocks[index(x, y, z)] = block;
    }

    inline const Vector3f& getPosition(void) const{
        return _position;
    }
};

#endif //GAMEENGINE_CHUNKSECTION_H
