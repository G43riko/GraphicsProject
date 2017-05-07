//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H


#include <src/core/BasicScene.h>
#include <src/components/terrain/TerrainManager.h>
class BasicScene;

class Scene : public BasicScene{
    private:
        PointerRawModel sphereModel = nullptr;
    public:
        inline Scene(Loader loader, PointerCubeTexture sky = nullptr) : BasicScene(sky){}

        void addObject(PointerGameObject object) override{
            objects.push_back(object);
            entities.addEntity(object->getObject());
        }
        void removeObject(PointerGameObject object){
            for(auto iter = objects.begin(); iter != objects.end(); ++iter){
                if( *iter == object ){
                    objects.erase(iter);
                    break;
                }
            }
            entities.removeEntity(object ->getObject());
        };
        void update(float delta) override{
            particles.update(delta);

            if(objects.size()){
                auto itObj = objects.begin();
                while(itObj != objects.end()){
                    itObj -> get() -> update(delta);
                    Vector3f position = itObj -> get() -> getNextPos();
                    float height = IS_NULL(getTerrainManager()) ? DEFAULT_TERRAIN_HEIGHT : getTerrainManager() -> getHeight(position.x, position.z);
                    if(position.y <= height){
                        itObj -> get() -> hitFloor(height);
                    }
                    itObj++;
                }
            }
            entities.update(delta);
        };

        void cleanUp(void) override{
            sky -> cleanUp();
        };

        inline PointerRawModel getSphereModel(void) const{
            return sphereModel;
        };
};


#endif //GRAPHICSPROJECT_SCENE_H
