//
// Created by gabriel on 13.5.2017.
//


#ifndef GAMEENGINE_VOXELRENDERER_H
#define GAMEENGINE_VOXELRENDERER_H

class VoxelRenderer{
    BasicShader * _shader;
public:
    inline VoxelRenderer(BasicShader * shader) : _shader(shader){}

    inline void prepare(BasicCamera& camera,
                        const std::vector<PointerPointLight>& lights,
                        const Texture2D& texture,
                        const PointerDirectionalLight sun = nullptr) const{
        _shader -> bind();
        _shader -> updateUniform4m(UNIFORM_VIEW_MATRIX, camera.getViewMatrix());
        _shader -> updateUniform3f(UNIFORM_CAMERA_POSITION, camera.getTransform() -> getPosition());
        _shader -> updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, Matrix4f::initTranslation(0, 0, 0));
        _shader -> updateMaterial(UNIFORM_MATERIAL, BlockTypes::getMaterialOf(BlockIDs::GRASS));

        texture.bind();

        ITERATE_VECTOR(lights, i){
            _shader -> updateLight("lightData[" + std::to_string(i) + "]", lights[i] -> getData());
        }

        if(IS_NOT_NULL(sun)){
            _shader -> updateLight("sun", sun -> getData());
        }
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    inline void render(const RawModel& model) const{
        RenderUtil::prepareModel(model, 3);
        glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
    }

    inline void finish(void) const{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        RenderUtil::finishRender(3);
    }
};

#endif //GAMEENGINE_VOXELRENDERER_H
