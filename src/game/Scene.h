//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H


#include <src/core/BasicScene.h>
#include <src/components/terrain/TerrainManager.h>

class Scene : public BasicScene{
    PointerRawModel sphereModel = nullptr;
public:
    inline Scene(Loader loader, PointerCubeTexture sky = nullptr) : BasicScene(sky){}

    void addObject(PointerGameObject object) override{
        objects.push_back(object);
        entities.addEntity(object->getObject());
    }
    void removeObject(PointerGameObject object){
        //for(auto iter = objects.begin(); iter != objects.end(); ++iter){
        ITERATE_VECTOR_ITERATOR_AUTO(objects, iter){
            if( *iter == object ){
                objects.erase(iter);
                break;
            }
        }
        entities.removeEntity(object ->getObject());
    };
    void update(float delta) override{
        particles.update(delta);
        Vector3f position;
        ITERATE_VECTOR(objects, i){
            objects[i] -> update(delta);
            position = objects[i] -> getNextPos();
            const float height = IS_NULL(getTerrainManager()) ? DEFAULT_TERRAIN_HEIGHT : getTerrainManager() -> getHeight(position.x, position.z);
            if(position.y <= height){
                objects[i] -> hitFloor(height);
            }
        }
        entities.update(delta);
    };

    void cleanUp(void) override{
        if(IS_NOT_NULL(sky)){
            sky -> cleanUp();
        }
    };

    inline PointerRawModel getSphereModel(void) const{
        return sphereModel;
    };
};


#endif //GRAPHICSPROJECT_SCENE_H
