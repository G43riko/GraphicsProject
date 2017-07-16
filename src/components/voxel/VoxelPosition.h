//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_VOXELPOSITION_H
#define GAMEENGINE_VOXELPOSITION_H

#include <src/utils/math/objects/Vectors.h>

class VoxelPosition{
    Vector3f _chunk;
    Vector2f _world;
    uint _offset;
public:
    inline VoxelPosition(const Vector2f& world = {}, const Vector3f& chunk = {}, const uint offset = 0) :
            _chunk(chunk),
            _world(world),
            _offset(offset){};

    //GETTERS

    inline const Vector3f& getChunkPosition(void) const{ return _chunk; }
    inline const Vector2f& getWorldPosition(void) const{ return _world; }
    inline uint getVerticalOffset(void) const{ return _offset; }

    //SETTERS

    inline void setVerticalOffset(uint offset){ _offset = offset; }
    inline void setWorldPosition(const Vector2f& world){ _world = world; }
};

#endif //GAMEENGINE_VOXELPOSITION_H
