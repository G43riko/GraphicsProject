//
// Created by gabriel on 13.5.2017.
//


#ifndef GAMEENGINE_VOXELRENDERER_H
#define GAMEENGINE_VOXELRENDERER_H

//#include <src/utils/Vectors.h>
//#include <src/core/BasicCamera.h>
//#include <src/rendering/Camera.h>
//#include <src/rendering/shader/VoxelShader.h>
//#include <src/rendering/RenderUtil.h>

#define NUMBER_OF_ATTRIBUTES 3

class VoxelRenderer{
    BasicShader * _shader;
public:
    inline VoxelRenderer(BasicShader * shader) : _shader(shader){}

    void prepare(PointerCamera camera, std::vector<PointerPointLight> lights, PointerTexture2D texture, PointerDirectionalLight sun){

        _shader -> bind();
//        _shader -> updateUniform4m(PROJECTION_MATRIX, camera -> getProjectionMatrix());
        _shader -> updateUniform4m(UNIFORM_VIEW_MATRIX, camera -> getViewMatrix());
        _shader -> updateUniform3f(UNIFORM_CAMERA_POSITION, camera -> getTransform() -> getPosition());

        texture -> bind();

        _shader -> updateMaterial(UNIFORM_MATERIAL, BlockTypes::getMaterialOf(BlockIDs::GRASS));

        for(unsigned int i=0 ; i<lights.size() ; i++){
            _shader -> updateLight("lightData[" + std::to_string(i) + "]", lights[i] -> getData());
        }

        if(IS_NOT_NULL(sun)){
            _shader -> updateLight("sun", sun -> getData());
        }
    }
    void render(Vector3f position, PointerRawModel model){
        RenderUtil::prepareModel(model, 3);
        _shader -> updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, Matrix4f::initTranslation(position.x, position.y, position.z));
        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }

    void finish(void){
        RenderUtil::finishRender(3);
    }
};

#endif //GAMEENGINE_VOXELRENDERER_H
