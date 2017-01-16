//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_ENTITYMASTER_H
#define GRAPHICSPROJECT_ENTITYMASTER_H

#include "../../rendering/RenderUtil.h"
#include "EntityManager.h"
#include <src/rendering/shader/EntityShader.cpp>

class EntityMaster {
private:
    BasicShader * shader = new EntityShader();
public:
    void renderEntities(EntitiesList entities, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane, Matrix4f toShadowSpace, GLuint shadowMap);
    void renderEntities(std::vector<PointerEntity> entities, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane, Matrix4f toShadowSpace, GLuint shadowMap);
    void renderEntity(PointerEntity entity, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane);
    EntityMaster(PointerCamera camera){
        RenderUtil::updateProjectionMatrix(shader, camera);
    };
    void cleanUp(void){
        shader -> cleanUp();
        delete shader;
    };
    BasicShader * getShader(void){
        return shader;
    };
};


#endif //GRAPHICSPROJECT_ENTITYMASTER_H
