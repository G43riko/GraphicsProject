//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_ENTITYMASTER_H
#define GRAPHICSPROJECT_ENTITYMASTER_H

#include "../../rendering/RenderUtil.h"
#include "EntityManager.h"
#include <src/rendering/Camera.h>
#include <src/components/Master.h>
#include <src/rendering/shader/EntityShader.h>
#include <src/rendering/shader/WireframeShader.h>
class Master;
class EntityMaster {
private:
    BasicShader * shader = new EntityShader();
    BasicShader * wireFrameShader = new WireframeShader();
public:
    void renderEntities(EntitiesList entities,
                        std::vector<PointerPointLight> lights,
                        PointerCamera camera,
                        int options,
                        Vector4f clipPlane,
                        Master& master);

    void renderEntities(std::vector<PointerEntity> entities,
                        std::vector<PointerPointLight> lights,
                        PointerCamera camera,
                        int options,
                        Vector4f clipPlane,
                        Master& master);

    void renderEntity(PointerEntity entity,
                      std::vector<PointerPointLight> lights,
                      PointerCamera camera,
                      int options,
                      Vector4f clipPlane);

    void renderWireFrame(EntitiesList entities, PointerCamera camera);
    EntityMaster(PointerCamera camera);
    void cleanUp(void);
    BasicShader * getShader(void);
};


#endif //GRAPHICSPROJECT_ENTITYMASTER_H
