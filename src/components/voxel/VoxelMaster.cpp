//
// Created by gabriel on 16.4.2017.
//

#include <src/rendering/RenderUtil.h>
#include "VoxelMaster.h"
#include "src/components/voxel_old/BlockTypes.h"

void VoxelMaster::renderBlock(Block *block) {
    if (IS_NULL(block)) {
        return;
    }
    if (!block->isVisible()) {
        return;
    }
}

void VoxelMaster::render(PointerCamera camera, std::vector<PointerPointLight> lights, PointerDirectionalLight sun) {

//    _world.render(renderer, camera, lights, texture, sun);
//    return;

    if(IS_NULL(world) || world -> blocks.empty()){
        return;
    }

    shader.bind();
    shader.updateUniform4m(UNIFORM_VIEW_MATRIX, camera -> getViewMatrix());
    shader.updateUniform3f(UNIFORM_CAMERA_POSITION, camera -> getTransform() -> getPosition());
//    shader -> updateUniform4m(PROJECTION_MATRIX, camera -> getProjectionMatrix());

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    PointerRawModel model = world -> getModel();
//    model = world->getBoxModel();
    RenderUtil::prepareModel(*model, 3);

    Vector3f position, scale;
    Matrix4f translation;

    Matrix4f scaleMat = Matrix4f::initScale(1, 1, 1);
    Matrix4f xPlusRotation  = scaleMat * Matrix4f::initRotation(0, 0, 90);
    Matrix4f xMinusRotation = scaleMat * Matrix4f::initRotation(0, 0, -90);
    Matrix4f yPlusRotation  = scaleMat * Matrix4f::initRotation(180, 0, 0);
    Matrix4f yMinusRotation = scaleMat * Matrix4f::initRotation(0, 0, 0);
    Matrix4f zPlusRotation  = scaleMat * Matrix4f::initRotation(-90, 0, 0);
    Matrix4f zMinusRotation = scaleMat * Matrix4f::initRotation(90, 0, 0);

    Vector3f cameraPosition = camera -> getPosition();
    if(IS_NOT_NULL(sun)){
        shader.updateLight("sun", sun -> getData());
    }
    ITERATE_VECTOR(lights, i){
//        RenderUtil::updateLightUniforms(lights[i], shader, camera, i, false);
        shader.updateLight("lightData[" + std::to_string(i) + "]", lights[i] -> getData());
    }

    //int threeFacesBoxes = 0;
    std::vector<Block *> blocks;
//    for(Block * block : world -> blocks){
    ITERATE_VECTOR(world -> blocks, i){
        if(!world -> blocks[i] -> isVisible() || world -> blocks[i] -> getRenderOptions() == 0){
            continue;
        }


        position = world -> blocks[i] -> getAbsolutePos();
        //scale = block -> getScale();
        translation = Matrix4f::initTranslation(position.x, position.y, position.z);
//        translation = *block -> getTranslation();
        shader.updateUniform4f("color", world -> blocks[i] -> getColor());
        shader.updateMaterial(UNIFORM_MATERIAL, BlockTypes::getMaterialOf(world -> blocks[i] -> getType()));

//      continue;
//        shader -> updateUniform4m(TRANSFORMATION_MATRIX, scaleMat * translation);
//        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
//        continue;

        int counter = 0;
//        if(block -> getRenderOptions() & Block::X_PLUS && position.x > cameraPosition.x) {counter++;}
//        if(block -> getRenderOptions() & Block::X_MINUS && position.x < cameraPosition.x) {counter++;}
//        if(block -> getRenderOptions() & Block::Y_PLUS && position.y > cameraPosition.y){counter++;}
//        if(block -> getRenderOptions() & Block::Y_MINUS && position.y < cameraPosition.y){counter++;}
//        if(block -> getRenderOptions() & Block::Z_PLUS && position.z > cameraPosition.z) {counter++;}
//        if(block -> getRenderOptions() & Block::Z_MINUS && position.z < cameraPosition.z) {counter++;}
        if(true || counter < 3){
            if(world -> blocks[i] -> getRenderOptions() & Block::X_PLUS && position.x > cameraPosition.x) {
                shader.updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, xPlusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(world -> blocks[i] -> getRenderOptions() & Block::X_MINUS && position.x < cameraPosition.x) {
                shader.updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, xMinusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(world -> blocks[i] -> getRenderOptions() & Block::Y_PLUS && position.y > cameraPosition.y){
                shader.updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, yPlusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(world -> blocks[i] -> getRenderOptions() & Block::Y_MINUS && position.y < cameraPosition.y){
                shader.updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, yMinusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(world -> blocks[i] -> getRenderOptions() & Block::Z_PLUS && position.z > cameraPosition.z) {
                shader.updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, zPlusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(world -> blocks[i] -> getRenderOptions() & Block::Z_MINUS && position.z < cameraPosition.z) {
                shader.updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, zMinusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
        }
        else{
                blocks.push_back(world -> blocks[i]);
        };
    }
    if(!blocks.empty()){
        model = world ->getBoxModel();
        RenderUtil::prepareModel(*model, 3);
        for(Block * block : blocks) {
            position = block -> getAbsolutePos();
            scale = block -> getScale();
            scaleMat = Matrix4f::initScale(scale.x, scale.y, scale.z);
            translation = Matrix4f::initTranslation(position.x, position.y, position.z);

            shader.updateUniform4f("color", block -> getColor());

            shader.updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, scaleMat * translation);
            glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
        }
    }

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//
//    glDisable(GL_BLEND);
    RenderUtil::finishRender(3);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}