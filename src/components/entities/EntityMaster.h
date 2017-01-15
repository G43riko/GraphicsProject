//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_ENTITYMASTER_H
#define GRAPHICSPROJECT_ENTITYMASTER_H

#include "../../rendering/RenderUtil.h"
#include "EntityManager.h"

class EntityMaster {
private:
    PointerBasicShader shader;
    RenderUtil * utils;
public:
    void renderEntities(EntitiesList entities, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane, Matrix4f toShadowSpace, GLuint shadowMap);
    void renderEntities(std::vector<PointerEntity> entities, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane, Matrix4f toShadowSpace, GLuint shadowMap);
    void renderEntity(PointerEntity entity, std::vector<PointerPointLight> lights, PointerCamera camera, int options, Vector4f clipPlane);
    EntityMaster(RenderUtil * utils, PointerBasicShader shader) : shader(shader), utils(utils){}
};


#endif //GRAPHICSPROJECT_ENTITYMASTER_H
