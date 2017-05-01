//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_VOXELRENDERER_H
#define GAMEENGINE_VOXELRENDERER_H

#include <src/rendering/shader/VoxelShader.h>
#include <src/rendering/Camera.h>
#include "World.h"
#include "../../rendering/RenderUtil.h"

#define NUM_X 8
#define NUM_Y 8

class World;

class VoxelMaster {
private:
    float object[NUM_X * NUM_Y];

    BasicShader *shader = new VoxelShader();
    World *world = nullptr;

    void renderBlock(Block *block);

public:
    VoxelMaster(PointerCamera camera){
        RenderUtil::updateProjectionMatrix(shader, camera);
        for(int i = NUM_X * NUM_Y - 1; i>=0 ; i--){
            object[i] = (float)random(0.95, 1.05);
        }
        shader->updateUniformNf("colorMatrix", object, NUM_X * NUM_Y);
    }
    void setWorld(World * world){
        this -> world = world;
    }
    void render(PointerCamera camera, std::vector<PointerPointLight> lights);

    void cleanUp(void) {
        shader->cleanUp();
        delete shader;

        CHECK_AND_CLEAR(world);
    };

    inline World * getWorld(void) const{
        return world;
    }
    inline BasicShader *getShader(void) const{
        return shader;
    };
};

#endif //GAMEENGINE_VOXELRENDERER_H
