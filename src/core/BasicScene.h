//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICSCENE_H
#define GRAPHICSPROJECT_BASICSCENE_H

#include "src/components/lights/PointLight.h"
#include <src/components/entities/EntityManager.h>
#include <src/components/particles/ParticleManager.h>
#include <src/game/GameObject.h>

class TerrainManager;

class BasicScene{
private:
    TerrainManager * _terrainManager = nullptr;
protected:

    PointerCubeTexture sky = nullptr;
    EntityManager entities;
    ParticleManager particles;
    std::vector<PointerPointLight> lights;
    std::vector<PointerGameObject> objects;
public:
    inline BasicScene(PointerCubeTexture sky = nullptr) : sky(sky){}
    virtual ~BasicScene(){};

    //OTHERS
    virtual void cleanUp(void) = 0;
    virtual void update(float delta) = 0;
    inline void loadParticleTexture(PointerTexture2D texture, int rows, int columns){
        particles.loadTexture(texture, rows, columns);
    }

    //ADDERS
    virtual void addObject(PointerGameObject object) = 0;
    virtual void removeObject(PointerGameObject object) = 0;


    inline void addLight(PointerPointLight light){ lights.push_back(light); }
    inline void addEntity(PointerEntity entity){ entities.addEntity(entity); }

    //CREATORS
    inline void createParticleSystem(PointerTexture2D texture, float pps, float speed, float gravityComplient, float lifeLength){
        particles.createSystem(texture, pps, speed, gravityComplient, lifeLength);

    }
    inline void createParticle(PointerTexture2D texture, const Vector3f &position, const Vector3f &velocity, float gravityEffect, float lifeLength, float rotation, float scale){
        particles.createParticle(texture, position, velocity, gravityEffect, lifeLength, rotation, scale);
    }

    //GETTERS
    inline std::vector<PointerPointLight> & getLights(void){ return lights; };
    inline std::vector<PointerGameObject> & getObjects(void){ return objects; };
    inline ParticlesList getParticles(void) const{ return particles.getParticles(); }
    inline EntitiesList  getEntities(void){ return entities.getEntities(); };
    inline PointerCubeTexture getSky(void) const{ return sky; };
    inline TerrainManager * getTerrainManager(void) const{ return _terrainManager; }
    //SETTERS
    inline void setSky(PointerCubeTexture sky){
        this -> sky = sky;
    }
    inline void setTerrainManager(TerrainManager * terrainManager){
        if(IS_NOT_NULL(_terrainManager)){
            /*
            _terrainManager->cleanUp();
            delete _terrainManager;
             */
            throw "nemôžeš priradiť terén keď už jeden existuje!!!";
        }
        _terrainManager = terrainManager;
    }
};

#endif //GRAPHICSPROJECT_BASICSCENE_H
