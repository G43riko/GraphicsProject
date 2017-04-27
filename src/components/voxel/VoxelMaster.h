//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_VOXELRENDERER_H
#define GAMEENGINE_VOXELRENDERER_H

#include <src/rendering/shader/VoxelShader.h>
#include <src/rendering/Camera.h>
#include "World.h"
#include "../../rendering/RenderUtil.h"

class World;

class VoxelMaster {
private:
    BasicShader *shader = new VoxelShader();
    World *world = nullptr;

    void renderBlock(Block *block);

public:
    VoxelMaster(PointerCamera camera){
        RenderUtil::updateProjectionMatrix(shader, camera);
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

    BasicShader *getShader(void) {
        return shader;
    };
};

#endif //GAMEENGINE_VOXELRENDERER_H
