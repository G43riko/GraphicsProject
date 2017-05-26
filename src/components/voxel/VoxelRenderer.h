//
// Created by gabriel on 13.5.2017.
//


#ifndef GAMEENGINE_VOXELRENDERER_H
#define GAMEENGINE_VOXELRENDERER_H

class VoxelRenderer{
    BasicShader * _shader;
public:
    inline VoxelRenderer(BasicShader * shader) : _shader(shader){}

    void prepare(PointerCamera camera, std::vector<PointerPointLight> lights, PointerTexture2D texture, PointerDirectionalLight sun){
        _shader -> bind();
        _shader -> updateUniform4m(UNIFORM_VIEW_MATRIX, camera -> getViewMatrix());
        _shader -> updateUniform3f(UNIFORM_CAMERA_POSITION, camera -> getTransform() -> getPosition());
        _shader -> updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, Matrix4f::initTranslation(0, 0, 0));
        _shader -> updateMaterial(UNIFORM_MATERIAL, BlockTypes::getMaterialOf(BlockIDs::GRASS));

        texture -> bind();

        ITERATE_VECTOR(lights, i){
            _shader -> updateLight("lightData[" + std::to_string(i) + "]", lights[i] -> getData());
        }

        if(IS_NOT_NULL(sun)){
            _shader -> updateLight("sun", sun -> getData());
        }
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    void render(PointerRawModel model){
        RenderUtil::prepareModel(model, 3);
        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
    }

    void finish(void){
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        RenderUtil::finishRender(3);
    }
};

#endif //GAMEENGINE_VOXELRENDERER_H
