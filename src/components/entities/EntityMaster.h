//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_ENTITYMASTER_H
#define GRAPHICSPROJECT_ENTITYMASTER_H

#include "../../rendering/RenderUtil.h"

class EntityMaster {
private:
    PointerBasicShader shader;
    RenderUtil * utils;
public:
    void renderEntities(std::vector<PointerEntity> entities, std::vector<PointerLight> lights, PointerCamera camera, int options, Vector4f clipPlane);
    void renderEntity(PointerEntity entity, std::vector<PointerLight> lights, PointerCamera camera, int options, Vector4f clipPlane);
    EntityMaster(RenderUtil * utils, PointerBasicShader shader) : shader(shader), utils(utils){}
};


#endif //GRAPHICSPROJECT_ENTITYMASTER_H
