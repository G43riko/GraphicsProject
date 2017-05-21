//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_VOXELWORLD_H
#define GAMEENGINE_VOXELWORLD_H

#include <unordered_map>
#include "src/components/voxel/chunks/VoxelChunk.h"
#include "VoxelRenderer.h"
#include "VoxelPosition.h"

typedef struct worldSettings{

}WorldSettings;

class VoxelWorld{
    std::unordered_map<std::string, VoxelChunk *> chunks;
    WorldSettings settings;
public:
    void render(VoxelRenderer renderer, PointerCamera camera, std::vector<PointerPointLight> lights, PointerTexture2D texture, PointerDirectionalLight sun) const{
        renderer.prepare(camera, lights, texture, sun);

        VoxelPosition position;

        ITERATE_MAP_AUTO(chunks, chunk){
            position.setWorldPosition(Vector2f(chunk -> first));
            chunk -> second -> render(renderer, position);
        }

        renderer.finish();
    }
    void generateChunk(Vector2f pos, Loader * loader){
        chunks[pos.toString()] = new VoxelChunk(pos, loader);
    }
    void generateChunk(int x, int y, int z, Loader * loader){
    }
};
#endif //GAMEENGINE_VOXELWORLD_H
