//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H


#include <src/rendering/model/Entity.h>
#include "src/entities/Light.h"
#include "GameObject.h"
#include <map>
#include <algorithm>
#include <src/entities/Particle.h>
#include <src/rendering/Renderer.h>

class Scene {
    private:
        constexpr static float SIZE = 500;
        PointerRawModel guiModel = nullptr;
        PointerRawModel sphereModel = nullptr;
        PointerRawModel skyModel = nullptr;
        PointerRawModel particleModel = nullptr;
        CubeTexture sky;
        std::vector<Particle> particles;
        static std::vector<GLfloat> guiVertices;
        static std::vector<GLfloat> particeVertices;
        static std::vector<float> VERTICES;
        std::vector<PointerEntity> entities;
        std::vector<PointerLight> lights;
        std::vector<PointerGameObject> objects;
    public:
        Scene(Loader, CubeTexture);

        void addLight(PointerLight light){
            lights.push_back(light);
        }
        void addEntity(PointerEntity entity){
            entities.push_back(entity);
        }

        void addParticle(Particle particle){
            particles.push_back(particle);
        }
        void addObject(PointerGameObject object){
            objects.push_back(object);
            entities.push_back(object->getObject());
        }

        void update(float delta){
            if(particles.size()){
                auto itPart = particles.begin();
                while(itPart != particles.end()){
                    bool stillAlive = itPart -> update(delta);
                    if(stillAlive)
                        itPart++;
                    else
                        itPart = particles.erase(itPart);
                }
            }
            if(objects.size()){
                auto itObj = objects.begin();
                while(itObj != objects.end()){
                    itObj -> get() -> update(delta);
                    itObj++;
                }
            }
            if(entities.size()){
                auto itEnt = entities.begin();
                while(itEnt != entities.end()){
                    if(itEnt -> get() -> isAlive())
                        itEnt++;
                    else
                        itEnt = entities.erase(itEnt);
                }
            }
        }

//        PointerEntity removeEntity(PointerEntity element){
//            entities.erase(std::remove(entities.begin(), entities.end(), element), entities.end());
//        }


        void cleanUp(){
            sky.cleanUp();
        }

        std::vector<PointerLight> getLights(){
            return lights;
        };

        std::vector<PointerEntity> getEntities(){
            return entities;
        };
        std::vector<PointerGameObject> getObjects(){
            return objects;
        };
        std::vector<Particle> getParticles(){
            return particles;
        };

        PointerRawModel getGuiModel(void){
            return guiModel;
        };
        PointerRawModel getParticleModel(void){
            return particleModel;
        };
        CubeTexture getSky(void){
            return sky;
        }
        PointerRawModel getSphereModel(void){
            return sphereModel;
        };
        PointerRawModel getSkyModel(void){
            return skyModel;
        };
};


#endif //GRAPHICSPROJECT_SCENE_H
