//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H


#include <src/core/BasicScene.h>

class BasicScene;

class Scene : public BasicScene{
    private:
        PointerRawModel sphereModel = nullptr;
        PointerCubeTexture sky = nullptr;
        EntityManager entities;
        ParticleManager particles;
//        std::vector<Particle> particles;
        std::vector<PointerPointLight> lights;
        std::vector<PointerGameObject> objects;
    public:
        Scene(Loader, PointerCubeTexture = nullptr);

        void loadParticleTexture(PointerTexture2D texture, int rows, int columns){
            particles.loadTexture(texture, rows, columns);
        }

        void setSky(PointerCubeTexture sky) override{
            this -> sky = sky;
        }
        void addLight(PointerPointLight light) override{
            lights.push_back(light);
        }
        void addEntity(PointerEntity entity) override{
            entities.addEntity(entity);
        }
        void createParticleSystem(PointerTexture2D texture, float pps, float speed, float gravityComplient, float lifeLength){
            particles.createSystem(texture, pps, speed, gravityComplient, lifeLength);

        }
        void createParticle(PointerTexture2D texture, const Vector3f &position, const Vector3f &velocity, float gravityEffect, float lifeLength, float rotation, float scale){
            particles.createParticle(texture, position, velocity, gravityEffect, lifeLength, rotation, scale);
        }
        /*
        void addParticle(Particle particle){
            particles.push_back(particle);
//            if(particles2.find(particle.getTexture()) == particles2.end()){
//                //neexistuje
//            }
        }
         */
        void addObject(PointerGameObject object) override{
            objects.push_back(object);
            //entities.push_back(object->getObject());
            entities.addEntity(object->getObject());
        }

        void update(float delta) override{
            particles.update(delta);
            /*
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
            */
            if(objects.size()){
                auto itObj = objects.begin();
                while(itObj != objects.end()){
                    itObj -> get() -> update(delta);
                    itObj++;
                }
            }
            entities.update(delta);
        };

        void cleanUp(void) override{
            sky -> cleanUp();
        };

        std::vector<PointerPointLight> getLights(void) override{
            return lights;
        };

        EntitiesList getEntities(void) override{
            return entities.getEntities();
        };

        std::vector<PointerGameObject> getObjects(void) override{
            return objects;
        };
        ParticlesList getParticles(void) override{
            return particles.getParticles();
        }
        /*
        std::vector<Particle> getParticles(void){
            return particles;
        };
        */

        PointerCubeTexture getSky(void) override{
            return sky;
        };

        PointerRawModel getSphereModel(void){
            return sphereModel;
        };
};


#endif //GRAPHICSPROJECT_SCENE_H
