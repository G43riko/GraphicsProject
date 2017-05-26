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
    inline EntityMaster(PointerCamera camera){
        RenderUtil::updateProjectionMatrix(*shader, camera);
    }
    void renderEntities(EntitiesList entities,
                        std::vector<PointerPointLight> lights,
                        PointerCamera camera,
                        int options,
                        Vector4f clipPlane,
                        Master& master);

    void renderWireFrame(EntitiesList entities, PointerCamera camera);


    inline void cleanUp(void) const{
        shader -> cleanUp();
        delete shader;
    }

    inline BasicShader * getShader(void) const{
        return shader;
    }
    /*
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
    */
};


#endif //GRAPHICSPROJECT_ENTITYMASTER_H
