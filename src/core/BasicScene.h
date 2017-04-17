//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICSCENE_H
#define GRAPHICSPROJECT_BASICSCENE_H

#include "src/components/lights/PointLight.h"
#include <src/components/entities/EntityManager.h>
#include <src/components/particles/ParticleManager.h>
#include <src/game/GameObject.h>


class BasicScene{
public:
    virtual ~BasicScene(){};
    virtual void cleanUp(void) = 0;
    virtual void update(float delta) = 0;
    virtual void setSky(PointerCubeTexture sky) = 0;
    virtual void addLight(PointerPointLight light) = 0;

    virtual void addEntity(PointerEntity entity) = 0;
    virtual void addObject(PointerGameObject object) = 0;

    //GETTERS
    virtual std::vector<PointerPointLight> getLights() = 0;

    virtual EntitiesList getEntities() = 0;

    virtual std::vector<PointerGameObject> getObjects() = 0;
    virtual ParticlesList getParticles(void) = 0;
    virtual PointerCubeTexture getSky(void) = 0;
};

#endif //GRAPHICSPROJECT_BASICSCENE_H
