//
// Created by gabriel on 16.4.2017.
//

#include <src/rendering/RenderUtil.h>
#include "VoxelMaster.h"
void VoxelMaster::renderBlock(Block *block) {
    if (block == nullptr) {
        return;
    }
    if (!block->isVisible()) {
        return;
    }
}

void VoxelMaster::render(PointerCamera camera) {//TODO memory leak
    if(world -> blocks.empty()){
        return;
    }
    shader -> bind();
    shader -> updateUniform4m(VIEW_MATRIX, camera -> getViewMatrix());
    shader -> updateUniform4m(PROJECTION_MATRIX, camera -> getProjectionMatrix());
//    glActiveTexture(GL_TEXTURE3);
    PointerRawModel model = world -> getModel();
    RenderUtil::prepareModel(model, 1);

    Vector3f position;
    Matrix4f translation;


//    glDisable(GL_CULL_FACE);
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    for(Block * block : world -> blocks){
        if(!block -> isVisible() || block -> getRenderOptions() == 0){
            continue;
        }
        position = block -> getAbsolutePosition();
        translation = Matrix4f::initTranslation(position.x, position.y, position.z);
        shader -> updateUniform4f("color", block -> getColor());
        Vector3f po = camera -> getPosition();
        if(block -> getRenderOptions() & Block::Y_MINUS && position.y < po.y){
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::Y_PLUS && position.y > po.y){
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(180, 0, 0) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::X_PLUS && position.x > po.x) {
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(0, 0, 90) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::X_MINUS && position.x < po.x) {
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(0, 0, -90) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::Z_MINUS && position.z < po.z) {
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(90, 0, 0) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::Z_PLUS && position.z > po.z) {
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(-90, 0, 0) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
    }

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//
//    glDisable(GL_BLEND);
    RenderUtil::finishRender(3);
}