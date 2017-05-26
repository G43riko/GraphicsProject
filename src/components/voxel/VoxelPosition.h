//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_VOXELPOSITION_H
#define GAMEENGINE_VOXELPOSITION_H

#include <src/utils/math/objects/Vectors.h>

class VoxelPosition{
    Vector3f _chunk;
    Vector2f _world;
    unsigned int _offset;
public:
    inline VoxelPosition(Vector2f world = {}, Vector3f chunk = {}, unsigned int offset = 0) :
            _chunk(chunk),
            _world(world),
            _offset(offset){};

    //GETTERS

    inline Vector3f getChunkPosition(void) const{ return _chunk; }
    inline Vector2f getWorldPosition(void) const{ return _world; }
    inline unsigned int getVerticalOffset(void) const{ return _offset; }

    //SETTERS

    inline void setVerticalOffset(unsigned int offset){ _offset = offset; }
    inline void setWorldPosition(Vector2f world){ _world = world; }
};

#endif //GAMEENGINE_VOXELPOSITION_H
