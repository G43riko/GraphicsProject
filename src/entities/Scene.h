//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H


#include <src/rendering/model/Entity.h>
#include "Light.h"
#include <map>
#include <src/entities/Particle.h>
#include <src/rendering/Renderer.h>

class Scene {
    private:
        PointerRawModel guiModel = nullptr;
        PointerRawModel sphereModel = nullptr;
        PointerRawModel skyModel = nullptr;
        PointerRawModel particleModel = nullptr;
        CubeTexture sky;
        std::vector<Particle> particles;
        static std::vector<GLfloat> guiVertices;
        static std::vector<GLfloat> particeVertices;
        constexpr static float SIZE = 500;
        static std::vector<float> VERTICES;
        std::vector<PointerEntity> entities;
        std::vector<PointerLight> lights;
    public:
        Scene(Loader, CubeTexture);
        void addLight(PointerLight light){
            lights.push_back(light);
        }
        void addEntity(PointerEntity entity){
            entities.push_back(entity);
        }

        void update(float delta){
            auto it = particles.begin();
            while(it != particles.end()){
                bool stillAlive = it -> update(delta);
                if(stillAlive)
                    it++;
                else
                    it = particles.erase(it);
            }

        }

        void addParticle(Particle particle){
            particles.push_back(particle);
        }

        void cleanUp(){
            sky.cleanUp();
        }

        std::vector<PointerLight> getLights(){
            return lights;
        };

        std::vector<PointerEntity> getEntities(){
            return entities;
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
