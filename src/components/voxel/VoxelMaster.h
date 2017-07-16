//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_VOXELMASTER_H
#define GAMEENGINE_VOXELMASTER_H

#include <src/rendering/shader/VoxelShader.h>
#include <src/rendering/Camera.h>
#include "src/components/voxel_old/World_old.h"
#include "src/rendering/RenderUtil.h"
#include "src/components/voxel/VoxelWorld.h"



//class World_old;
class VoxelMaster {
private:
    float object[WOXEL_TEXTURE_NUM_X * WOXEL_TEXTURE_NUM_Y];

    VoxelShader shader = VoxelShader();
    World_old * world = nullptr;
    VoxelWorld _world;
    void renderBlock(Block *block);
    VoxelRenderer renderer;
    PointerTexture2D texture;
public:
    VoxelMaster(BasicCamera& camera, PointerTexture2D texture) : renderer(VoxelRenderer(&shader)){
        RenderUtil::updateProjectionMatrix(shader, camera);
        for(int i = WOXEL_TEXTURE_NUM_X * WOXEL_TEXTURE_NUM_Y - 1; i>=0 ; i--){
            object[i] = (float)grandom(0.95, 1.05);
        }
        shader.updateUniformNf("colorMatrix", object, WOXEL_TEXTURE_NUM_X * WOXEL_TEXTURE_NUM_Y);
    }
    void setWorld(World_old * world){
        this -> world = world;
    }
    void render(PointerCamera camera, std::vector<PointerPointLight> lights, PointerDirectionalLight sun = nullptr);
    void setTexture(PointerTexture2D texture){this->texture = texture;};
    void cleanUp(void) {
        shader.cleanUp();

        CHECK_AND_CLEAR(world);
    };
    void generateChunk(Vector2f pos, Loader * loader){
        _world.generateChunk(pos, loader);
    }

    inline World_old * getWorld(void) const{
        return world;
    }
    inline BasicShader& getShader(void){
        return shader;
    };
};

#endif //GAMEENGINE_VOXELMASTER_H
