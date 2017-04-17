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

void VoxelMaster::render(PointerCamera camera) {
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
    for(Block * block : world -> blocks){
        if(!block -> isVisible() || block -> getRenderOptions() == 0){
            continue;
        }
        position = block -> getAbsolutePosition();
        translation = Matrix4f::initTranslation(position.x, position.y, position.z);
        shader -> updateUniform4f("color", block -> getColor());

        if(block -> getRenderOptions() & Block::Y_MINUS){
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(0, 0, 0) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::Y_PLUS){
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(180, 0, 0) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::X_PLUS) {
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(0, 0, 90) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::X_MINUS) {
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(0, 0, -90) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::Z_MINUS) {
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(90, 0, 0) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        if(block -> getRenderOptions() & Block::Z_PLUS) {
            shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(-90, 0, 0) * translation);
            glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
        }
    }
    RenderUtil::finishRender(3);
}