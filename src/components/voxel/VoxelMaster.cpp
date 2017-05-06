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

void VoxelMaster::render(PointerCamera camera, std::vector<PointerPointLight> lights) {
    if(world == nullptr || world -> blocks.empty()){
        return;
    }

    shader -> bind();
    shader -> updateUniform4m(VIEW_MATRIX, camera -> getViewMatrix());
    shader -> updateUniform3f(CAMERA_POSITION, *camera -> getTransform() -> getPosition());
//    shader -> updateUniform4m(PROJECTION_MATRIX, camera -> getProjectionMatrix());

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    PointerRawModel model = world -> getModel();
//    model = world->getBoxModel();
    RenderUtil::prepareModel(model, 3);

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

    for(unsigned int i=0 ; i<lights.size() ; i++){
        RenderUtil::updateLightUniforms(lights[i], shader, camera, i, false);
    }

    //int threeFacesBoxes = 0;
    std::vector<Block *> blocks;
    for(Block * block : world -> blocks){
        if(!block -> isVisible() || block -> getRenderOptions() == 0){
            continue;
        }


        position = block -> getAbsolutePos();
        //scale = block -> getScale();
        translation = Matrix4f::initTranslation(position.x, position.y, position.z);
//        translation = *block -> getTranslation();
        shader -> updateUniform4f("color", block -> getColor());

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
            if(block -> getRenderOptions() & Block::X_PLUS && position.x > cameraPosition.x) {
                shader -> updateUniform4m(TRANSFORMATION_MATRIX, xPlusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(block -> getRenderOptions() & Block::X_MINUS && position.x < cameraPosition.x) {
                shader -> updateUniform4m(TRANSFORMATION_MATRIX, xMinusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(block -> getRenderOptions() & Block::Y_PLUS && position.y > cameraPosition.y){
                shader -> updateUniform4m(TRANSFORMATION_MATRIX, yPlusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(block -> getRenderOptions() & Block::Y_MINUS && position.y < cameraPosition.y){
                shader -> updateUniform4m(TRANSFORMATION_MATRIX, yMinusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(block -> getRenderOptions() & Block::Z_PLUS && position.z > cameraPosition.z) {
                shader -> updateUniform4m(TRANSFORMATION_MATRIX, zPlusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            if(block -> getRenderOptions() & Block::Z_MINUS && position.z < cameraPosition.z) {
                shader -> updateUniform4m(TRANSFORMATION_MATRIX, zMinusRotation * translation);
                glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
            }
        }
        else{
                blocks.push_back(block);
        };
    }
    if(!blocks.empty()){
        model = world ->getBoxModel();
        RenderUtil::prepareModel(model, 3);
        for(Block * block : blocks) {
            position = block -> getAbsolutePos();
            scale = block -> getScale();
            Matrix4f scaleMat = Matrix4f::initScale(scale.x, scale.y, scale.z);
            translation = Matrix4f::initTranslation(position.x, position.y, position.z);

            shader -> updateUniform4f("color", block -> getColor());

            shader->updateUniform4m(TRANSFORMATION_MATRIX, scaleMat * translation);
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